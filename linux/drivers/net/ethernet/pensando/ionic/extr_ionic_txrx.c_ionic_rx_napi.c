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
typedef  int u32 ;
struct napi_struct {int dummy; } ;
struct ionic_qcq {int dummy; } ;
struct ionic_lif {TYPE_3__* txqcqs; TYPE_1__* ionic; } ;
struct ionic_dev {int /*<<< orphan*/  intr_ctrl; } ;
struct ionic_cq {TYPE_5__* bound_intr; TYPE_4__* bound_q; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
struct TYPE_9__ {unsigned int index; struct ionic_lif* lif; } ;
struct TYPE_8__ {TYPE_2__* qcq; } ;
struct TYPE_7__ {struct ionic_cq cq; } ;
struct TYPE_6__ {struct ionic_dev idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STATS_INTR_REARM (TYPE_5__*) ; 
 int /*<<< orphan*/  DEBUG_STATS_NAPI_POLL (struct ionic_qcq*,int) ; 
 int IONIC_INTR_CRED_RESET_COALESCE ; 
 int IONIC_INTR_CRED_UNMASK ; 
 int /*<<< orphan*/  ionic_intr_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ionic_rx_fill_cb (TYPE_4__*) ; 
 int ionic_rx_walk_cq (struct ionic_cq*,int) ; 
 int /*<<< orphan*/  ionic_tx_flush (struct ionic_cq*) ; 
 scalar_t__ napi_complete_done (struct napi_struct*,int) ; 
 struct ionic_cq* napi_to_cq (struct napi_struct*) ; 
 struct ionic_qcq* napi_to_qcq (struct napi_struct*) ; 

int ionic_rx_napi(struct napi_struct *napi, int budget)
{
	struct ionic_qcq *qcq = napi_to_qcq(napi);
	struct ionic_cq *rxcq = napi_to_cq(napi);
	unsigned int qi = rxcq->bound_q->index;
	struct ionic_dev *idev;
	struct ionic_lif *lif;
	struct ionic_cq *txcq;
	u32 work_done = 0;
	u32 flags = 0;

	lif = rxcq->bound_q->lif;
	idev = &lif->ionic->idev;
	txcq = &lif->txqcqs[qi].qcq->cq;

	ionic_tx_flush(txcq);

	work_done = ionic_rx_walk_cq(rxcq, budget);

	if (work_done)
		ionic_rx_fill_cb(rxcq->bound_q);

	if (work_done < budget && napi_complete_done(napi, work_done)) {
		flags |= IONIC_INTR_CRED_UNMASK;
		DEBUG_STATS_INTR_REARM(rxcq->bound_intr);
	}

	if (work_done || flags) {
		flags |= IONIC_INTR_CRED_RESET_COALESCE;
		ionic_intr_credits(idev->intr_ctrl, rxcq->bound_intr->index,
				   work_done, flags);
	}

	DEBUG_STATS_NAPI_POLL(qcq, work_done);

	return work_done;
}