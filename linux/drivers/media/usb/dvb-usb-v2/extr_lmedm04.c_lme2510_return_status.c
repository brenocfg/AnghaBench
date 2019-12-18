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
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  info (char*,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lme2510_return_status(struct dvb_usb_device *d)
{
	int ret;
	u8 *data;

	data = kzalloc(6, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0),
			      0x06, 0x80, 0x0302, 0x00,
			      data, 0x6, 200);
	if (ret != 6)
		ret = -EINVAL;
	else
		ret = data[2];

	info("Firmware Status: %6ph", data);

	kfree(data);
	return ret;
}