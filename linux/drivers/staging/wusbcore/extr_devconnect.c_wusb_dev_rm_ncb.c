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
struct wusb_dev {int /*<<< orphan*/ * usb_dev; } ;
struct usb_device {scalar_t__ wusb; int devnum; struct wusb_dev* wusb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  wusb_dev_bos_rm (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_put (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_sec_rm (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_sysfs_rm (struct wusb_dev*) ; 

__attribute__((used)) static void wusb_dev_rm_ncb(struct usb_device *usb_dev)
{
	struct wusb_dev *wusb_dev = usb_dev->wusb_dev;

	if (usb_dev->wusb == 0 || usb_dev->devnum == 1)
		return;		/* skip non wusb and wusb RHs */

	wusb_dev_sysfs_rm(wusb_dev);
	wusb_dev_bos_rm(wusb_dev);
	wusb_dev_sec_rm(wusb_dev);
	wusb_dev->usb_dev = NULL;
	usb_dev->wusb_dev = NULL;
	wusb_dev_put(wusb_dev);
	usb_put_dev(usb_dev);
}