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
struct wdm_device {int /*<<< orphan*/  service_outs_intr; int /*<<< orphan*/  rxwork; int /*<<< orphan*/  wlock; int /*<<< orphan*/  rlock; int /*<<< orphan*/  wait; int /*<<< orphan*/  iuspin; int /*<<< orphan*/  rerr; int /*<<< orphan*/  flags; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  WDM_IN_USE ; 
 int /*<<< orphan*/  WDM_READ ; 
 int /*<<< orphan*/  WDM_RESETTING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 struct wdm_device* wdm_find_device (struct usb_interface*) ; 

__attribute__((used)) static int wdm_pre_reset(struct usb_interface *intf)
{
	struct wdm_device *desc = wdm_find_device(intf);

	/*
	 * we notify everybody using poll of
	 * an exceptional situation
	 * must be done before recovery lest a spontaneous
	 * message from the device is lost
	 */
	spin_lock_irq(&desc->iuspin);
	set_bit(WDM_RESETTING, &desc->flags);	/* inform read/write */
	set_bit(WDM_READ, &desc->flags);	/* unblock read */
	clear_bit(WDM_IN_USE, &desc->flags);	/* unblock write */
	desc->rerr = -EINTR;
	spin_unlock_irq(&desc->iuspin);
	wake_up_all(&desc->wait);
	mutex_lock(&desc->rlock);
	mutex_lock(&desc->wlock);
	kill_urbs(desc);
	cancel_work_sync(&desc->rxwork);
	cancel_work_sync(&desc->service_outs_intr);
	return 0;
}