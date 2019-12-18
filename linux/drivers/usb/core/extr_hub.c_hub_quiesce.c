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
struct TYPE_4__ {int /*<<< orphan*/  clear_work; scalar_t__ hub; } ;
struct usb_hub {int quiescing; TYPE_2__ tt; int /*<<< orphan*/  leds; scalar_t__ has_indicators; int /*<<< orphan*/  urb; int /*<<< orphan*/  irq_urb_retry; TYPE_1__** ports; int /*<<< orphan*/  irq_urb_lock; struct usb_device* hdev; } ;
struct usb_device {int maxchild; } ;
typedef  enum hub_quiescing_type { ____Placeholder_hub_quiescing_type } hub_quiescing_type ;
struct TYPE_3__ {scalar_t__ child; } ;

/* Variables and functions */
 int HUB_SUSPEND ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_disconnect (scalar_t__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hub_quiesce(struct usb_hub *hub, enum hub_quiescing_type type)
{
	struct usb_device *hdev = hub->hdev;
	unsigned long flags;
	int i;

	/* hub_wq and related activity won't re-trigger */
	spin_lock_irqsave(&hub->irq_urb_lock, flags);
	hub->quiescing = 1;
	spin_unlock_irqrestore(&hub->irq_urb_lock, flags);

	if (type != HUB_SUSPEND) {
		/* Disconnect all the children */
		for (i = 0; i < hdev->maxchild; ++i) {
			if (hub->ports[i]->child)
				usb_disconnect(&hub->ports[i]->child);
		}
	}

	/* Stop hub_wq and related activity */
	del_timer_sync(&hub->irq_urb_retry);
	usb_kill_urb(hub->urb);
	if (hub->has_indicators)
		cancel_delayed_work_sync(&hub->leds);
	if (hub->tt.hub)
		flush_work(&hub->tt.clear_work);
}