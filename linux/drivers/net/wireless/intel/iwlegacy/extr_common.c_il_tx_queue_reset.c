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
typedef  size_t u32 ;
struct il_tx_queue {int /*<<< orphan*/  q; scalar_t__ need_update; int /*<<< orphan*/  meta; } ;
struct il_priv {size_t cmd_queue; TYPE_1__* ops; struct il_tx_queue* txq; } ;
struct il_cmd_meta {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* txq_init ) (struct il_priv*,struct il_tx_queue*) ;} ;

/* Variables and functions */
 int TFD_CMD_SLOTS ; 
 int TFD_TX_CMD_SLOTS ; 
 int /*<<< orphan*/  il_queue_init (struct il_priv*,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*,struct il_tx_queue*) ; 

void
il_tx_queue_reset(struct il_priv *il, u32 txq_id)
{
	int slots, actual_slots;
	struct il_tx_queue *txq = &il->txq[txq_id];

	if (txq_id == il->cmd_queue) {
		slots = TFD_CMD_SLOTS;
		actual_slots = TFD_CMD_SLOTS + 1;
	} else {
		slots = TFD_TX_CMD_SLOTS;
		actual_slots = TFD_TX_CMD_SLOTS;
	}

	memset(txq->meta, 0, sizeof(struct il_cmd_meta) * actual_slots);
	txq->need_update = 0;

	/* Initialize queue's high/low-water marks, and head/tail idxes */
	il_queue_init(il, &txq->q, slots, txq_id);

	/* Tell device where to find queue */
	il->ops->txq_init(il, txq);
}