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
typedef  int u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_POWER ; 
 int ttusb2_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttusb2_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	u8 b = onoff;
	ttusb2_msg(d, CMD_POWER, &b, 0, NULL, 0);
	return ttusb2_msg(d, CMD_POWER, &b, 1, NULL, 0);
}