#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct bnad_rx_info {scalar_t__ rx_id; int /*<<< orphan*/ * rx; TYPE_4__* rx_ctrl; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_comp; } ;
struct bnad {int cfg_flags; int /*<<< orphan*/  bna_lock; TYPE_2__ bnad_completions; int /*<<< orphan*/  dim_timer; int /*<<< orphan*/  run_flags; TYPE_1__* rx_res_info; struct bna_rx_config* rx_config; struct bnad_rx_info* rx_info; } ;
struct bna_rx_config {int /*<<< orphan*/  num_paths; } ;
struct bna_res_info {int dummy; } ;
struct TYPE_8__ {TYPE_3__* ccb; } ;
struct TYPE_7__ {scalar_t__ intr_type; } ;
struct TYPE_5__ {struct bna_res_info* res_info; } ;

/* Variables and functions */
 int BNAD_CF_DIM_ENABLED ; 
 int /*<<< orphan*/  BNAD_RF_DIM_TIMER_RUNNING ; 
 int /*<<< orphan*/  BNA_HARD_CLEANUP ; 
 scalar_t__ BNA_INTR_T_MSIX ; 
 int /*<<< orphan*/  bna_rx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_rx_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_cb_rx_disabled ; 
 int /*<<< orphan*/  bnad_napi_delete (struct bnad*,size_t) ; 
 int /*<<< orphan*/  bnad_rx_msix_unregister (struct bnad*,struct bnad_rx_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_rx_res_free (struct bnad*,struct bna_res_info*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void
bnad_destroy_rx(struct bnad *bnad, u32 rx_id)
{
	struct bnad_rx_info *rx_info = &bnad->rx_info[rx_id];
	struct bna_rx_config *rx_config = &bnad->rx_config[rx_id];
	struct bna_res_info *res_info = &bnad->rx_res_info[rx_id].res_info[0];
	unsigned long flags;
	int to_del = 0;

	if (!rx_info->rx)
		return;

	if (0 == rx_id) {
		spin_lock_irqsave(&bnad->bna_lock, flags);
		if (bnad->cfg_flags & BNAD_CF_DIM_ENABLED &&
		    test_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags)) {
			clear_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags);
			to_del = 1;
		}
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		if (to_del)
			del_timer_sync(&bnad->dim_timer);
	}

	init_completion(&bnad->bnad_completions.rx_comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_disable(rx_info->rx, BNA_HARD_CLEANUP, bnad_cb_rx_disabled);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	wait_for_completion(&bnad->bnad_completions.rx_comp);

	if (rx_info->rx_ctrl[0].ccb->intr_type == BNA_INTR_T_MSIX)
		bnad_rx_msix_unregister(bnad, rx_info, rx_config->num_paths);

	bnad_napi_delete(bnad, rx_id);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_destroy(rx_info->rx);

	rx_info->rx = NULL;
	rx_info->rx_id = 0;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	bnad_rx_res_free(bnad, res_info);
}