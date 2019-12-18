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
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int pl2303_vendor_read (struct usb_serial*,int,int*) ; 
 int pl2303_vendor_write (struct usb_serial*,int,int) ; 

__attribute__((used)) static int pl2303_update_reg(struct usb_serial *serial, u8 reg, u8 mask, u8 val)
{
	int ret = 0;
	u8 *buf;

	buf = kmalloc(1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = pl2303_vendor_read(serial, reg | 0x80, buf);
	if (ret)
		goto out_free;

	*buf &= ~mask;
	*buf |= val & mask;

	ret = pl2303_vendor_write(serial, reg, *buf);
out_free:
	kfree(buf);

	return ret;
}