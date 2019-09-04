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
struct dln2_rx_context {int /*<<< orphan*/  done; struct urb* urb; scalar_t__ in_use; } ;
struct dln2_mod_rx_slots {int /*<<< orphan*/  lock; struct dln2_rx_context* slots; } ;
struct dln2_dev {struct dln2_mod_rx_slots* mod_rx_slots; TYPE_1__* interface; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 size_t DLN2_MAX_RX_SLOTS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool dln2_transfer_complete(struct dln2_dev *dln2, struct urb *urb,
				   u16 handle, u16 rx_slot)
{
	struct device *dev = &dln2->interface->dev;
	struct dln2_mod_rx_slots *rxs = &dln2->mod_rx_slots[handle];
	struct dln2_rx_context *rxc;
	unsigned long flags;
	bool valid_slot = false;

	if (rx_slot >= DLN2_MAX_RX_SLOTS)
		goto out;

	rxc = &rxs->slots[rx_slot];

	spin_lock_irqsave(&rxs->lock, flags);
	if (rxc->in_use && !rxc->urb) {
		rxc->urb = urb;
		complete(&rxc->done);
		valid_slot = true;
	}
	spin_unlock_irqrestore(&rxs->lock, flags);

out:
	if (!valid_slot)
		dev_warn(dev, "bad/late response %d/%d\n", handle, rx_slot);

	return valid_slot;
}