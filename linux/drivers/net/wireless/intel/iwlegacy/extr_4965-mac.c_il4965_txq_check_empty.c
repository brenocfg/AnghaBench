#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_10__ {int state; int txq_id; } ;
struct il_tid_data {TYPE_5__ agg; int /*<<< orphan*/  tfds_in_queue; int /*<<< orphan*/  seq_number; } ;
struct il_queue {int /*<<< orphan*/  write_ptr; int /*<<< orphan*/  read_ptr; } ;
struct il_priv {int /*<<< orphan*/  vif; TYPE_4__* stations; int /*<<< orphan*/  sta_lock; TYPE_1__* txq; } ;
struct TYPE_7__ {size_t* addr; } ;
struct TYPE_8__ {TYPE_2__ sta; } ;
struct TYPE_9__ {struct il_tid_data* tid; TYPE_3__ sta; } ;
struct TYPE_6__ {struct il_queue q; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_HT (char*) ; 
 int /*<<< orphan*/  IEEE80211_SEQ_TO_SN (int /*<<< orphan*/ ) ; 
 int IL_AGG_OFF ; 
 int IL_AGG_ON ; 
#define  IL_EMPTYING_HW_QUEUE_ADDBA 129 
#define  IL_EMPTYING_HW_QUEUE_DELBA 128 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (int /*<<< orphan*/ ,size_t*,size_t) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (int /*<<< orphan*/ ,size_t*,size_t) ; 
 int il4965_get_fifo_from_tid (size_t) ; 
 int /*<<< orphan*/  il4965_txq_agg_disable (struct il_priv*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int
il4965_txq_check_empty(struct il_priv *il, int sta_id, u8 tid, int txq_id)
{
	struct il_queue *q = &il->txq[txq_id].q;
	u8 *addr = il->stations[sta_id].sta.sta.addr;
	struct il_tid_data *tid_data = &il->stations[sta_id].tid[tid];

	lockdep_assert_held(&il->sta_lock);

	switch (il->stations[sta_id].tid[tid].agg.state) {
	case IL_EMPTYING_HW_QUEUE_DELBA:
		/* We are reclaiming the last packet of the */
		/* aggregated HW queue */
		if (txq_id == tid_data->agg.txq_id &&
		    q->read_ptr == q->write_ptr) {
			u16 ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
			int tx_fifo = il4965_get_fifo_from_tid(tid);
			D_HT("HW queue empty: continue DELBA flow\n");
			il4965_txq_agg_disable(il, txq_id, ssn, tx_fifo);
			tid_data->agg.state = IL_AGG_OFF;
			ieee80211_stop_tx_ba_cb_irqsafe(il->vif, addr, tid);
		}
		break;
	case IL_EMPTYING_HW_QUEUE_ADDBA:
		/* We are reclaiming the last packet of the queue */
		if (tid_data->tfds_in_queue == 0) {
			D_HT("HW queue empty: continue ADDBA flow\n");
			tid_data->agg.state = IL_AGG_ON;
			ieee80211_start_tx_ba_cb_irqsafe(il->vif, addr, tid);
		}
		break;
	}

	return 0;
}