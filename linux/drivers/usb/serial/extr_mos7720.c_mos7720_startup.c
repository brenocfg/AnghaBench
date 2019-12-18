#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct usb_serial {TYPE_2__** port; struct usb_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;
struct urb {int /*<<< orphan*/  complete; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_4__ {struct urb* interrupt_in_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MOS7720_LSR ; 
 scalar_t__ MOSCHIP_DEVICE_ID_7715 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos7715_interrupt_callback ; 
 int mos7715_parport_init (struct usb_serial*) ; 
 int /*<<< orphan*/  read_mos_reg (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mos7720_startup(struct usb_serial *serial)
{
	struct usb_device *dev;
	char data;
	u16 product;
	int ret_val;

	product = le16_to_cpu(serial->dev->descriptor.idProduct);
	dev = serial->dev;

	/* setting configuration feature to one */
	usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			(__u8)0x03, 0x00, 0x01, 0x00, NULL, 0x00, 5000);

	if (product == MOSCHIP_DEVICE_ID_7715) {
		struct urb *urb = serial->port[0]->interrupt_in_urb;

		urb->complete = mos7715_interrupt_callback;

#ifdef CONFIG_USB_SERIAL_MOS7715_PARPORT
		ret_val = mos7715_parport_init(serial);
		if (ret_val < 0)
			return ret_val;
#endif
	}
	/* start the interrupt urb */
	ret_val = usb_submit_urb(serial->port[0]->interrupt_in_urb, GFP_KERNEL);
	if (ret_val) {
		dev_err(&dev->dev, "failed to submit interrupt urb: %d\n",
			ret_val);
	}

	/* LSR For Port 1 */
	read_mos_reg(serial, 0, MOS7720_LSR, &data);
	dev_dbg(&dev->dev, "LSR:%x\n", data);

	return 0;
}