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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TECH_LED_BLINK ; 
 int /*<<< orphan*/  disable_led_control ; 
 int technisat_usb2_get_ir (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  technisat_usb2_set_led (struct dvb_usb_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int technisat_usb2_rc_query(struct dvb_usb_device *d)
{
	int ret = technisat_usb2_get_ir(d);

	if (ret < 0)
		return ret;

	if (ret == 0)
		return 0;

	if (!disable_led_control)
		technisat_usb2_set_led(d, 1, TECH_LED_BLINK);

	return 0;
}