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
struct bnad_tx_info {struct bna_tcb** tcb; } ;
struct bnad {int dummy; } ;
struct bna_tcb {size_t id; struct bna_tcb* priv; TYPE_2__* txq; } ;
struct TYPE_4__ {TYPE_1__* tx; } ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */

__attribute__((used)) static void
bnad_cb_tcb_setup(struct bnad *bnad, struct bna_tcb *tcb)
{
	struct bnad_tx_info *tx_info =
			(struct bnad_tx_info *)tcb->txq->tx->priv;

	tcb->priv = tcb;
	tx_info->tcb[tcb->id] = tcb;
}