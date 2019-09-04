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
struct TYPE_2__ {int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; } ;
struct ldc_channel {int flags; int /*<<< orphan*/  rx_base; int /*<<< orphan*/  rx_num_entries; int /*<<< orphan*/  tx_base; int /*<<< orphan*/  tx_num_entries; int /*<<< orphan*/  id; TYPE_1__ cfg; } ;

/* Variables and functions */
 int LDC_FLAG_ALLOCED_QUEUES ; 
 int LDC_FLAG_REGISTERED_IRQS ; 
 int LDC_FLAG_REGISTERED_QUEUES ; 
 int /*<<< orphan*/  LDC_STATE_INIT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ldc_channel*) ; 
 int /*<<< orphan*/  free_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldc_set_state (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4v_ldc_rx_qconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4v_ldc_tx_qconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ldc_unbind(struct ldc_channel *lp)
{
	if (lp->flags & LDC_FLAG_REGISTERED_IRQS) {
		free_irq(lp->cfg.rx_irq, lp);
		free_irq(lp->cfg.tx_irq, lp);
		lp->flags &= ~LDC_FLAG_REGISTERED_IRQS;
	}

	if (lp->flags & LDC_FLAG_REGISTERED_QUEUES) {
		sun4v_ldc_tx_qconf(lp->id, 0, 0);
		sun4v_ldc_rx_qconf(lp->id, 0, 0);
		lp->flags &= ~LDC_FLAG_REGISTERED_QUEUES;
	}
	if (lp->flags & LDC_FLAG_ALLOCED_QUEUES) {
		free_queue(lp->tx_num_entries, lp->tx_base);
		free_queue(lp->rx_num_entries, lp->rx_base);
		lp->flags &= ~LDC_FLAG_ALLOCED_QUEUES;
	}

	ldc_set_state(lp, LDC_STATE_INIT);
}