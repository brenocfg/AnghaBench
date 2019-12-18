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
struct adbhid {int /*<<< orphan*/  id; } ;

/* Variables and functions */
#define  EV_LED 128 
 int /*<<< orphan*/  LED_CAPSL ; 
 int /*<<< orphan*/  LED_NUML ; 
 int /*<<< orphan*/  LED_SCROLLL ; 
 struct adbhid* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  real_leds (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adbhid_kbd_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
	struct adbhid *adbhid = input_get_drvdata(dev);
	unsigned char leds;

	switch (type) {
	case EV_LED:
		leds =  (test_bit(LED_SCROLLL, dev->led) ? 4 : 0) |
			(test_bit(LED_NUML,    dev->led) ? 1 : 0) |
			(test_bit(LED_CAPSL,   dev->led) ? 2 : 0);
		real_leds(leds, adbhid->id);
		return 0;
	}

	return -1;
}