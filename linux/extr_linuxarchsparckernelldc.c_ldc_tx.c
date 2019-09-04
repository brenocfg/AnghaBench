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
struct TYPE_2__ {scalar_t__ mode; } ;
struct ldc_channel {unsigned long chan_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  hs_state; TYPE_1__ cfg; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_head; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long LDC_CHANNEL_UP ; 
 unsigned int LDC_EVENT_UP ; 
 int /*<<< orphan*/  LDC_HS_COMPLETE ; 
 scalar_t__ LDC_MODE_RAW ; 
 int /*<<< orphan*/  LDC_STATE_CONNECTED ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  ldc_set_state (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_events (struct ldc_channel*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun4v_ldc_tx_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static irqreturn_t ldc_tx(int irq, void *dev_id)
{
	struct ldc_channel *lp = dev_id;
	unsigned long flags, orig_state;
	unsigned int event_mask = 0;

	spin_lock_irqsave(&lp->lock, flags);

	orig_state = lp->chan_state;

	/* We should probably check for hypervisor errors here and
	 * reset the LDC channel if we get one.
	 */
	sun4v_ldc_tx_get_state(lp->id,
			       &lp->tx_head,
			       &lp->tx_tail,
			       &lp->chan_state);

	ldcdbg(TX, " TX state[0x%02lx:0x%02lx] head[0x%04lx] tail[0x%04lx]\n",
	       orig_state, lp->chan_state, lp->tx_head, lp->tx_tail);

	if (lp->cfg.mode == LDC_MODE_RAW &&
	    lp->chan_state == LDC_CHANNEL_UP) {
		lp->hs_state = LDC_HS_COMPLETE;
		ldc_set_state(lp, LDC_STATE_CONNECTED);

		/*
		 * Generate an LDC_EVENT_UP event if the channel
		 * was not already up.
		 */
		if (orig_state != LDC_CHANNEL_UP) {
			event_mask |= LDC_EVENT_UP;
			orig_state = lp->chan_state;
		}
	}

	spin_unlock_irqrestore(&lp->lock, flags);

	send_events(lp, event_mask);

	return IRQ_HANDLED;
}