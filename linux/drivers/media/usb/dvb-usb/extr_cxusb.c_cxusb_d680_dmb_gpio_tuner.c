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
 int /*<<< orphan*/  CMD_GPIO_WRITE ; 
 int EIO ; 
 int cxusb_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  deb_info (char*) ; 

__attribute__((used)) static int cxusb_d680_dmb_gpio_tuner(struct dvb_usb_device *d,
				     u8 addr, int onoff)
{
	u8  o[2] = {addr, onoff};
	u8  i;
	int rc;

	rc = cxusb_ctrl_msg(d, CMD_GPIO_WRITE, o, 2, &i, 1);

	if (rc < 0)
		return rc;

	if (i == 0x01)
		return 0;

	deb_info("gpio_write failed.\n");
	return -EIO;
}