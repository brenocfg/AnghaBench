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
struct bnad_tx_info {int /*<<< orphan*/  tx_cleanup_work; struct bna_tcb** tcb; } ;
struct bnad {int /*<<< orphan*/  work_q; } ;
struct bna_tx {scalar_t__ priv; } ;
struct bna_tcb {int dummy; } ;

/* Variables and functions */
 int BNAD_MAX_TXQ_PER_TX ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnad_cb_tx_cleanup(struct bnad *bnad, struct bna_tx *tx)
{
	struct bnad_tx_info *tx_info = (struct bnad_tx_info *)tx->priv;
	struct bna_tcb *tcb;
	int i;

	for (i = 0; i < BNAD_MAX_TXQ_PER_TX; i++) {
		tcb = tx_info->tcb[i];
		if (!tcb)
			continue;
	}

	queue_delayed_work(bnad->work_q, &tx_info->tx_cleanup_work, 0);
}