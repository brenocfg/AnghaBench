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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dibusb_i2c_msg (struct dvb_usb_device*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

int dibusb_read_eeprom_byte(struct dvb_usb_device *d, u8 offs, u8 *val)
{
	u8 *buf;
	int rc;

	buf = kmalloc(2, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[0] = offs;

	rc = dibusb_i2c_msg(d, 0x50, &buf[0], 1, &buf[1], 1);
	*val = buf[1];
	kfree(buf);

	return rc;
}