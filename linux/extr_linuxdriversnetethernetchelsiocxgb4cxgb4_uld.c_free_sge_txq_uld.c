#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sge_uld_txq_info {int ntxq; struct sge_uld_txq* uldtxq; } ;
struct TYPE_3__ {int /*<<< orphan*/  sdesc; int /*<<< orphan*/  in_use; int /*<<< orphan*/  cntxt_id; scalar_t__ desc; } ;
struct sge_uld_txq {TYPE_1__ q; int /*<<< orphan*/  sendq; int /*<<< orphan*/  qresume_tsk; } ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_tx_desc (struct adapter*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_txq (struct adapter*,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_ofld_eq_free (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_sge_txq_uld(struct adapter *adap, struct sge_uld_txq_info *txq_info)
{
	int nq = txq_info->ntxq;
	int i;

	for (i = 0; i < nq; i++) {
		struct sge_uld_txq *txq = &txq_info->uldtxq[i];

		if (txq && txq->q.desc) {
			tasklet_kill(&txq->qresume_tsk);
			t4_ofld_eq_free(adap, adap->mbox, adap->pf, 0,
					txq->q.cntxt_id);
			free_tx_desc(adap, &txq->q, txq->q.in_use, false);
			kfree(txq->q.sdesc);
			__skb_queue_purge(&txq->sendq);
			free_txq(adap, &txq->q);
		}
	}
}