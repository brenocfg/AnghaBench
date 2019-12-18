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
struct wdm_device {int /*<<< orphan*/  count; int /*<<< orphan*/  device_list; int /*<<< orphan*/  rlock; int /*<<< orphan*/  wlock; int /*<<< orphan*/  service_outs_intr; int /*<<< orphan*/  rxwork; int /*<<< orphan*/  wait; int /*<<< orphan*/  iuspin; int /*<<< orphan*/  flags; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDM_DISCONNECTING ; 
 int /*<<< orphan*/  WDM_READ ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup (struct wdm_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdm_class ; 
 int /*<<< orphan*/  wdm_device_list_lock ; 
 struct wdm_device* wdm_find_device (struct usb_interface*) ; 
 int /*<<< orphan*/  wdm_mutex ; 

__attribute__((used)) static void wdm_disconnect(struct usb_interface *intf)
{
	struct wdm_device *desc;
	unsigned long flags;

	usb_deregister_dev(intf, &wdm_class);
	desc = wdm_find_device(intf);
	mutex_lock(&wdm_mutex);

	/* the spinlock makes sure no new urbs are generated in the callbacks */
	spin_lock_irqsave(&desc->iuspin, flags);
	set_bit(WDM_DISCONNECTING, &desc->flags);
	set_bit(WDM_READ, &desc->flags);
	spin_unlock_irqrestore(&desc->iuspin, flags);
	wake_up_all(&desc->wait);
	mutex_lock(&desc->rlock);
	mutex_lock(&desc->wlock);
	kill_urbs(desc);
	cancel_work_sync(&desc->rxwork);
	cancel_work_sync(&desc->service_outs_intr);
	mutex_unlock(&desc->wlock);
	mutex_unlock(&desc->rlock);

	/* the desc->intf pointer used as list key is now invalid */
	spin_lock(&wdm_device_list_lock);
	list_del(&desc->device_list);
	spin_unlock(&wdm_device_list_lock);

	if (!desc->count)
		cleanup(desc);
	else
		dev_dbg(&intf->dev, "%d open files - postponing cleanup\n", desc->count);
	mutex_unlock(&wdm_mutex);
}