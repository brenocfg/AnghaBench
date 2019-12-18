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
typedef  int u32 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int REQUEST_JUMPRAM ; 
 int /*<<< orphan*/  deb_fw (char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int dib0700_jumpram(struct usb_device *udev, u32 address)
{
	int ret = 0, actlen;
	u8 *buf;

	buf = kmalloc(8, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	buf[0] = REQUEST_JUMPRAM;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = (address >> 24) & 0xff;
	buf[5] = (address >> 16) & 0xff;
	buf[6] = (address >> 8)  & 0xff;
	buf[7] =  address        & 0xff;

	if ((ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, 0x01),buf,8,&actlen,1000)) < 0) {
		deb_fw("jumpram to 0x%x failed\n",address);
		goto out;
	}
	if (actlen != 8) {
		deb_fw("jumpram to 0x%x failed\n",address);
		ret = -EIO;
		goto out;
	}
out:
	kfree(buf);
	return ret;
}