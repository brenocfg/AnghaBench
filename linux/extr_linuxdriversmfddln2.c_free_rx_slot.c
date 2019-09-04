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
typedef  size_t u16 ;
struct urb {int dummy; } ;
struct dln2_rx_context {int in_use; int /*<<< orphan*/  done; struct urb* urb; } ;
struct dln2_mod_rx_slots {int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; struct dln2_rx_context* slots; int /*<<< orphan*/  bmap; } ;
struct dln2_dev {TYPE_1__* interface; struct dln2_mod_rx_slots* mod_rx_slots; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_rx_slot(struct dln2_dev *dln2, u16 handle, int slot)
{
	struct dln2_mod_rx_slots *rxs;
	struct urb *urb = NULL;
	unsigned long flags;
	struct dln2_rx_context *rxc;

	rxs = &dln2->mod_rx_slots[handle];

	spin_lock_irqsave(&rxs->lock, flags);

	clear_bit(slot, rxs->bmap);

	rxc = &rxs->slots[slot];
	rxc->in_use = false;
	urb = rxc->urb;
	rxc->urb = NULL;
	reinit_completion(&rxc->done);

	spin_unlock_irqrestore(&rxs->lock, flags);

	if (urb) {
		int err;
		struct device *dev = &dln2->interface->dev;

		err = usb_submit_urb(urb, GFP_KERNEL);
		if (err < 0)
			dev_err(dev, "failed to resubmit RX URB: %d\n", err);
	}

	wake_up_interruptible(&rxs->wq);
}