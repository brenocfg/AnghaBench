#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct urb {int dummy; } ;
struct peak_usb_device {TYPE_1__* adapter; } ;
struct TYPE_2__ {int (* dev_restart_async ) (struct peak_usb_device*,struct urb*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCAN_USB_MAX_CMD_LEN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peak_usb_restart_complete (struct peak_usb_device*) ; 
 int stub1 (struct peak_usb_device*,struct urb*,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static int peak_usb_restart(struct peak_usb_device *dev)
{
	struct urb *urb;
	int err;
	u8 *buf;

	/*
	 * if device doesn't define any asynchronous restart handler, simply
	 * wake the netdev queue up
	 */
	if (!dev->adapter->dev_restart_async) {
		peak_usb_restart_complete(dev);
		return 0;
	}

	/* first allocate a urb to handle the asynchronous steps */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		return -ENOMEM;

	/* also allocate enough space for the commands to send */
	buf = kmalloc(PCAN_USB_MAX_CMD_LEN, GFP_ATOMIC);
	if (!buf) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	/* call the device specific handler for the restart */
	err = dev->adapter->dev_restart_async(dev, urb, buf);
	if (!err)
		return 0;

	kfree(buf);
	usb_free_urb(urb);

	return err;
}