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
struct technisat_usb2_state {int power_state; } ;
struct dvb_usb_device {struct technisat_usb2_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TECH_LED_OFF ; 
 int /*<<< orphan*/  TECH_LED_ON ; 
 scalar_t__ disable_led_control ; 
 int /*<<< orphan*/  technisat_usb2_set_led (struct dvb_usb_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int technisat_usb2_power_ctrl(struct dvb_usb_device *d, int level)
{
	struct technisat_usb2_state *state = d->priv;

	state->power_state = level;

	if (disable_led_control)
		return 0;

	/* green led is turned off in any case - will be turned on when tuning */
	technisat_usb2_set_led(d, 0, TECH_LED_OFF);
	/* red led is turned on all the time */
	technisat_usb2_set_led(d, 1, TECH_LED_ON);
	return 0;
}