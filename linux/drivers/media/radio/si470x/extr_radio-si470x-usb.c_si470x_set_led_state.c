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
struct si470x_device {unsigned char* usb_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char LED_COMMAND ; 
 unsigned char LED_REPORT ; 
 int /*<<< orphan*/  LED_REPORT_SIZE ; 
 int si470x_set_report (struct si470x_device*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si470x_set_led_state(struct si470x_device *radio,
		unsigned char led_state)
{
	int retval;

	radio->usb_buf[0] = LED_REPORT;
	radio->usb_buf[1] = LED_COMMAND;
	radio->usb_buf[2] = led_state;

	retval = si470x_set_report(radio, radio->usb_buf, LED_REPORT_SIZE);

	return (retval < 0) ? -EINVAL : 0;
}