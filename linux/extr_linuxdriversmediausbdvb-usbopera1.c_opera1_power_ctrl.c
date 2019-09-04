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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPERA_WRITE_MSG ; 
 scalar_t__ dvb_usb_opera1_debug ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int opera1_xilinx_rw (int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opera1_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	u8 val = onoff ? 0x01 : 0x00;

	if (dvb_usb_opera1_debug)
		info("power %s", onoff ? "on" : "off");
	return opera1_xilinx_rw(d->udev, 0xb7, val,
				&val, 1, OPERA_WRITE_MSG);
}