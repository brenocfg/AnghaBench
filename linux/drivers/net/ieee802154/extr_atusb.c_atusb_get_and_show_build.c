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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct atusb {struct usb_device* usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATUSB_BUILD ; 
 scalar_t__ ATUSB_BUILD_SIZE ; 
 int /*<<< orphan*/  ATUSB_REQ_FROM_DEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int atusb_control_msg (struct atusb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atusb_get_and_show_build(struct atusb *atusb)
{
	struct usb_device *usb_dev = atusb->usb_dev;
	char *build;
	int ret;

	build = kmalloc(ATUSB_BUILD_SIZE + 1, GFP_KERNEL);
	if (!build)
		return -ENOMEM;

	ret = atusb_control_msg(atusb, usb_rcvctrlpipe(usb_dev, 0),
				ATUSB_BUILD, ATUSB_REQ_FROM_DEV, 0, 0,
				build, ATUSB_BUILD_SIZE, 1000);
	if (ret >= 0) {
		build[ret] = 0;
		dev_info(&usb_dev->dev, "Firmware: build %s\n", build);
	}

	kfree(build);
	return ret;
}