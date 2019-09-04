#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct bnad_tx_info {scalar_t__ tx_id; int /*<<< orphan*/ * tx; TYPE_3__** tcb; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_comp; } ;
struct bnad {int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  num_txq_per_tx; TYPE_2__ bnad_completions; TYPE_1__* tx_res_info; struct bnad_tx_info* tx_info; } ;
struct bna_res_info {int dummy; } ;
struct TYPE_6__ {scalar_t__ intr_type; } ;
struct TYPE_4__ {struct bna_res_info* res_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_HARD_CLEANUP ; 
 scalar_t__ BNA_INTR_T_MSIX ; 
 int /*<<< orphan*/  bna_tx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_tx_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_cb_tx_disabled ; 
 int /*<<< orphan*/  bnad_tx_msix_unregister (struct bnad*,struct bnad_tx_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_tx_res_free (struct bnad*,struct bna_res_info*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void
bnad_destroy_tx(struct bnad *bnad, u32 tx_id)
{
	struct bnad_tx_info *tx_info = &bnad->tx_info[tx_id];
	struct bna_res_info *res_info = &bnad->tx_res_info[tx_id].res_info[0];
	unsigned long flags;

	if (!tx_info->tx)
		return;

	init_completion(&bnad->bnad_completions.tx_comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_disable(tx_info->tx, BNA_HARD_CLEANUP, bnad_cb_tx_disabled);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	wait_for_completion(&bnad->bnad_completions.tx_comp);

	if (tx_info->tcb[0]->intr_type == BNA_INTR_T_MSIX)
		bnad_tx_msix_unregister(bnad, tx_info,
			bnad->num_txq_per_tx);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_destroy(tx_info->tx);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	tx_info->tx = NULL;
	tx_info->tx_id = 0;

	bnad_tx_res_free(bnad, res_info);
}