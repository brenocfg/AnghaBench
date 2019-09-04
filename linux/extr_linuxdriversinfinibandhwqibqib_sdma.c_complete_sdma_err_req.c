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
struct TYPE_4__ {int /*<<< orphan*/  list; scalar_t__ next_descq_idx; scalar_t__ start_idx; } ;
struct qib_verbs_txreq {TYPE_2__ txreq; TYPE_1__* qp; } ;
struct qib_qp_priv {int /*<<< orphan*/  s_dma_busy; } ;
struct qib_pportdata {int /*<<< orphan*/  sdma_activelist; } ;
struct TYPE_3__ {struct qib_qp_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_sdma_activelist (struct qib_pportdata*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void complete_sdma_err_req(struct qib_pportdata *ppd,
				  struct qib_verbs_txreq *tx)
{
	struct qib_qp_priv *priv = tx->qp->priv;

	atomic_inc(&priv->s_dma_busy);
	/* no sdma descriptors, so no unmap_desc */
	tx->txreq.start_idx = 0;
	tx->txreq.next_descq_idx = 0;
	list_add_tail(&tx->txreq.list, &ppd->sdma_activelist);
	clear_sdma_activelist(ppd);
}