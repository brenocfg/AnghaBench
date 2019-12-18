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
struct usb_interface {int dummy; } ;
struct most_dev {struct most_dev* ep_address; struct most_dev* conf; struct most_dev* cap; struct most_dev* busy_urbs; int /*<<< orphan*/  iface; TYPE_1__* dci; int /*<<< orphan*/  poll_work_obj; int /*<<< orphan*/  link_stat_timer; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/ * usb_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct most_dev*) ; 
 int /*<<< orphan*/  most_deregister_interface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct most_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdm_disconnect(struct usb_interface *interface)
{
	struct most_dev *mdev = usb_get_intfdata(interface);

	mutex_lock(&mdev->io_mutex);
	usb_set_intfdata(interface, NULL);
	mdev->usb_device = NULL;
	mutex_unlock(&mdev->io_mutex);

	del_timer_sync(&mdev->link_stat_timer);
	cancel_work_sync(&mdev->poll_work_obj);

	device_unregister(&mdev->dci->dev);
	most_deregister_interface(&mdev->iface);

	kfree(mdev->busy_urbs);
	kfree(mdev->cap);
	kfree(mdev->conf);
	kfree(mdev->ep_address);
	kfree(mdev);
}