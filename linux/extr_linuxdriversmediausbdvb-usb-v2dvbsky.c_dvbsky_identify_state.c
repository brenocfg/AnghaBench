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
 int WARM ; 
 int /*<<< orphan*/  dvbsky_gpio_ctrl (struct dvb_usb_device*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dvbsky_identify_state(struct dvb_usb_device *d, const char **name)
{
	dvbsky_gpio_ctrl(d, 0x04, 1);
	msleep(20);
	dvbsky_gpio_ctrl(d, 0x83, 0);
	dvbsky_gpio_ctrl(d, 0xc0, 1);
	msleep(100);
	dvbsky_gpio_ctrl(d, 0x83, 1);
	dvbsky_gpio_ctrl(d, 0xc0, 0);
	msleep(50);

	return WARM;
}