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
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;
struct ldc_channel {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__ cfg; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; int /*<<< orphan*/  hs_state; int /*<<< orphan*/  tx_head; int /*<<< orphan*/  tx_acked; int /*<<< orphan*/  chan_state; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  rx_num_entries; int /*<<< orphan*/  rx_ra; int /*<<< orphan*/  tx_num_entries; int /*<<< orphan*/  tx_ra; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  LDC_FLAG_REGISTERED_IRQS ; 
 int /*<<< orphan*/  LDC_FLAG_REGISTERED_QUEUES ; 
 int /*<<< orphan*/  LDC_HS_COMPLETE ; 
 int /*<<< orphan*/  LDC_HS_OPEN ; 
 scalar_t__ LDC_MODE_RAW ; 
 int /*<<< orphan*/  LDC_STATE_BOUND ; 
 scalar_t__ LDC_STATE_INIT ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ldc_channel*) ; 
 int /*<<< orphan*/  ldc_set_state (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long sun4v_ldc_rx_qconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long sun4v_ldc_tx_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long sun4v_ldc_tx_qconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ldc_bind(struct ldc_channel *lp)
{
	unsigned long hv_err, flags;
	int err = -EINVAL;

	if (lp->state != LDC_STATE_INIT)
		return -EINVAL;

	spin_lock_irqsave(&lp->lock, flags);

	enable_irq(lp->cfg.rx_irq);
	enable_irq(lp->cfg.tx_irq);

	lp->flags |= LDC_FLAG_REGISTERED_IRQS;

	err = -ENODEV;
	hv_err = sun4v_ldc_tx_qconf(lp->id, 0, 0);
	if (hv_err)
		goto out_free_irqs;

	hv_err = sun4v_ldc_tx_qconf(lp->id, lp->tx_ra, lp->tx_num_entries);
	if (hv_err)
		goto out_free_irqs;

	hv_err = sun4v_ldc_rx_qconf(lp->id, 0, 0);
	if (hv_err)
		goto out_unmap_tx;

	hv_err = sun4v_ldc_rx_qconf(lp->id, lp->rx_ra, lp->rx_num_entries);
	if (hv_err)
		goto out_unmap_tx;

	lp->flags |= LDC_FLAG_REGISTERED_QUEUES;

	hv_err = sun4v_ldc_tx_get_state(lp->id,
					&lp->tx_head,
					&lp->tx_tail,
					&lp->chan_state);
	err = -EBUSY;
	if (hv_err)
		goto out_unmap_rx;

	lp->tx_acked = lp->tx_head;

	lp->hs_state = LDC_HS_OPEN;
	ldc_set_state(lp, LDC_STATE_BOUND);

	if (lp->cfg.mode == LDC_MODE_RAW) {
		/*
		 * There is no handshake in RAW mode, so handshake
		 * is completed.
		 */
		lp->hs_state = LDC_HS_COMPLETE;
	}

	spin_unlock_irqrestore(&lp->lock, flags);

	return 0;

out_unmap_rx:
	lp->flags &= ~LDC_FLAG_REGISTERED_QUEUES;
	sun4v_ldc_rx_qconf(lp->id, 0, 0);

out_unmap_tx:
	sun4v_ldc_tx_qconf(lp->id, 0, 0);

out_free_irqs:
	lp->flags &= ~LDC_FLAG_REGISTERED_IRQS;
	free_irq(lp->cfg.tx_irq, lp);
	free_irq(lp->cfg.rx_irq, lp);

	spin_unlock_irqrestore(&lp->lock, flags);

	return err;
}