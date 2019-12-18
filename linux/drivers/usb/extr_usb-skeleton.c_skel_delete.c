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
struct usb_skel {struct usb_skel* bulk_in_buffer; int /*<<< orphan*/  udev; int /*<<< orphan*/  interface; int /*<<< orphan*/  bulk_in_urb; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_skel*) ; 
 struct usb_skel* to_skel_dev (struct kref*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skel_delete(struct kref *kref)
{
	struct usb_skel *dev = to_skel_dev(kref);

	usb_free_urb(dev->bulk_in_urb);
	usb_put_intf(dev->interface);
	usb_put_dev(dev->udev);
	kfree(dev->bulk_in_buffer);
	kfree(dev);
}