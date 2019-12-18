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
struct il_queue {scalar_t__ n_bd; scalar_t__ write_ptr; scalar_t__ read_ptr; } ;
struct il_tx_queue {struct il_queue q; } ;
struct il_priv {TYPE_1__* ops; struct il_tx_queue* txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* txq_free_tfd ) (struct il_priv*,struct il_tx_queue*) ;} ;

/* Variables and functions */
 scalar_t__ il_queue_inc_wrap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*,struct il_tx_queue*) ; 

void
il_tx_queue_unmap(struct il_priv *il, int txq_id)
{
	struct il_tx_queue *txq = &il->txq[txq_id];
	struct il_queue *q = &txq->q;

	if (q->n_bd == 0)
		return;

	while (q->write_ptr != q->read_ptr) {
		il->ops->txq_free_tfd(il, txq);
		q->read_ptr = il_queue_inc_wrap(q->read_ptr, q->n_bd);
	}
}