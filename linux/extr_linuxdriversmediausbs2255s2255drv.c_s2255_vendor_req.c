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
typedef  int /*<<< orphan*/  u16 ;
struct s2255_dev {int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long s2255_vendor_req(struct s2255_dev *dev, unsigned char Request,
			     u16 Index, u16 Value, void *TransferBuffer,
			     s32 TransferBufferLength, int bOut)
{
	int r;
	unsigned char *buf;

	buf = kmalloc(TransferBufferLength, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (!bOut) {
		r = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
				    Request,
				    USB_TYPE_VENDOR | USB_RECIP_DEVICE |
				    USB_DIR_IN,
				    Value, Index, buf,
				    TransferBufferLength, HZ * 5);

		if (r >= 0)
			memcpy(TransferBuffer, buf, TransferBufferLength);
	} else {
		memcpy(buf, TransferBuffer, TransferBufferLength);
		r = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
				    Request, USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				    Value, Index, buf,
				    TransferBufferLength, HZ * 5);
	}
	kfree(buf);
	return r;
}