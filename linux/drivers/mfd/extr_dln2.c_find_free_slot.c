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
typedef  size_t u16 ;
struct dln2_rx_context {int in_use; } ;
struct dln2_mod_rx_slots {int /*<<< orphan*/  lock; int /*<<< orphan*/  bmap; struct dln2_rx_context* slots; } ;
struct dln2_dev {struct dln2_mod_rx_slots* mod_rx_slots; scalar_t__ disconnect; } ;

/* Variables and functions */
 int DLN2_MAX_RX_SLOTS ; 
 int ENODEV ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool find_free_slot(struct dln2_dev *dln2, u16 handle, int *slot)
{
	struct dln2_mod_rx_slots *rxs;
	unsigned long flags;

	if (dln2->disconnect) {
		*slot = -ENODEV;
		return true;
	}

	rxs = &dln2->mod_rx_slots[handle];

	spin_lock_irqsave(&rxs->lock, flags);

	*slot = find_first_zero_bit(rxs->bmap, DLN2_MAX_RX_SLOTS);

	if (*slot < DLN2_MAX_RX_SLOTS) {
		struct dln2_rx_context *rxc = &rxs->slots[*slot];

		set_bit(*slot, rxs->bmap);
		rxc->in_use = true;
	}

	spin_unlock_irqrestore(&rxs->lock, flags);

	return *slot < DLN2_MAX_RX_SLOTS;
}