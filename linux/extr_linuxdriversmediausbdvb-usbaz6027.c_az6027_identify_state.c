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
struct usb_device {int dummy; } ;
struct dvb_usb_device_properties {int dummy; } ;
struct dvb_usb_device_description {int dummy; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  deb_info (char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int az6027_identify_state(struct usb_device *udev,
				 struct dvb_usb_device_properties *props,
				 struct dvb_usb_device_description **desc,
				 int *cold)
{
	u8 *b;
	s16 ret;

	b = kmalloc(16, GFP_KERNEL);
	if (!b)
		return -ENOMEM;

	ret = usb_control_msg(udev,
				  usb_rcvctrlpipe(udev, 0),
				  0xb7,
				  USB_TYPE_VENDOR | USB_DIR_IN,
				  6,
				  0,
				  b,
				  6,
				  USB_CTRL_GET_TIMEOUT);

	*cold = ret <= 0;
	kfree(b);
	deb_info("cold: %d\n", *cold);
	return 0;
}