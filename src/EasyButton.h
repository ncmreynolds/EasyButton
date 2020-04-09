/**
 * EasyButton.h
 * @author Evert Arias
 * @version 1.1.0
 * @license MIT
 */

#ifndef _EasyButton_h
#define _EasyButton_h

#include <Arduino.h>
#include "EasyButtonBase.h"
#include "Sequence.h"

#define EASYBUTTON_READ_TYPE_INTERRUPT 0
#define EASYBUTTON_READ_TYPE_POLL 1


class EasyButton:EasyButtonBase
{
	friend class EasyButtonTouch;

public:
	EasyButton(uint8_t pin, uint32_t debounce_time = 35, bool pullup_enable = true, bool invert = true) : _pin(pin), _db_time(debounce_time), _invert(invert), _pu_enabled(pullup_enable), _read_type(EASYBUTTON_READ_TYPE_POLL)
	{
	}
	~EasyButton() {}
	// PUBLIC FUNCTIONS
	virtual void begin();														// Initialize a button object and the pin it's connected to.
	bool read();																// Returns the current debounced button state, true for pressed, false for released.
	void update();																// Update button pressed time, only needed when using interrupts
	void enableInterrupt(callback_t callback);									// Call a callback function when the button is pressed or released
	void disableInterrupt();
	bool supportsInterrupt();			 // Returns true if the button pin is an external interrupt pin
	bool isPressed();					 // Returns true if the button state was pressed at the last read.
	bool isReleased();					 // Returns true if the button state was released at the last read.
	bool wasPressed();					 // Returns true if the button state at the last read was pressed.
	bool wasReleased();					 // Returns true if the button state at the last read was released.
	bool pressedFor(uint32_t duration);	 // Returns true if the button state at the last read was pressed, and has been in that state for at least the given number of milliseconds.
	bool releasedFor(uint32_t duration); // Returns true if the button state at the last read was released, and has been in that state for at least the given number of milliseconds.
private:
	// PRIVATE VARIABLES
	bool _was_btn_held;			// Indicate if button was held.
	bool _held_callback_called; // Indicate if button long press has been notified.
	uint8_t _pin;				// Arduino pin number where the Button is connected to.
	uint32_t _db_time;			// Debounce time (ms).
	bool _invert;				// Inverts button logic. If true, low = pressed else high = pressed.
	bool _pu_enabled;			// Internal pullup resistor enabled.
	bool _current_state;		// Current button state, true = pressed.
	bool _last_state;			// Previous button state, true = pressed.
	bool _changed;				// Has the state change since last read.
	uint32_t _time;				// Time of current state.
	uint32_t _last_change;		// Time of last state change.
	uint8_t _read_type;			// Read type. Poll or Interrupt


	virtual bool _readPin();  // Abstracts the pin value reading.
	void _checkPressedTime(); // Verify if pressed_for_callback should be called
};

#endif