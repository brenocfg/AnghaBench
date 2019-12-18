#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct input_dev {int /*<<< orphan*/  led; } ;

/* Variables and functions */
#define  KEY_CAPSLOCK 130 
#define  KEY_NUMLOCK 129 
#define  KEY_SCROLLLOCK 128 
 int LED_CAPSL ; 
 int LED_NUML ; 
 int LED_SCROLLL ; 
 int /*<<< orphan*/  __change_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_locking_key(struct input_dev *visorinput_dev, int keycode,
			       int desired_state)
{
	int led;

	switch (keycode) {
	case KEY_CAPSLOCK:
		led = LED_CAPSL;
		break;
	case KEY_SCROLLLOCK:
		led = LED_SCROLLL;
		break;
	case KEY_NUMLOCK:
		led = LED_NUML;
		break;
	default:
		led = -1;
		return;
	}
	if (test_bit(led, visorinput_dev->led) != desired_state) {
		input_report_key(visorinput_dev, keycode, 1);
		input_sync(visorinput_dev);
		input_report_key(visorinput_dev, keycode, 0);
		input_sync(visorinput_dev);
		__change_bit(led, visorinput_dev->led);
	}
}