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
struct iwl_rb_allocator {int /*<<< orphan*/  rx_alloc; } ;
struct iwl_trans_pcie {struct iwl_rxq* rxq; scalar_t__ base_rb_stts_dma; int /*<<< orphan*/ * base_rb_stts; struct iwl_rb_allocator rba; } ;
struct iwl_trans {size_t num_rx_queues; int /*<<< orphan*/  dev; TYPE_1__* trans_cfg; } ;
struct TYPE_4__ {scalar_t__ poll; } ;
struct iwl_rxq {TYPE_2__ napi; } ;
struct iwl_rb_status {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iwl_pcie_free_rbs_pool (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_free_rxq_dma (struct iwl_trans*,struct iwl_rxq*) ; 
 int /*<<< orphan*/  kfree (struct iwl_rxq*) ; 
 int /*<<< orphan*/  netif_napi_del (TYPE_2__*) ; 

void iwl_pcie_rx_free(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rb_allocator *rba = &trans_pcie->rba;
	int i;
	size_t rb_stts_size = trans->trans_cfg->device_family >=
			      IWL_DEVICE_FAMILY_22560 ?
			      sizeof(__le16) : sizeof(struct iwl_rb_status);

	/*
	 * if rxq is NULL, it means that nothing has been allocated,
	 * exit now
	 */
	if (!trans_pcie->rxq) {
		IWL_DEBUG_INFO(trans, "Free NULL rx context\n");
		return;
	}

	cancel_work_sync(&rba->rx_alloc);

	iwl_pcie_free_rbs_pool(trans);

	if (trans_pcie->base_rb_stts) {
		dma_free_coherent(trans->dev,
				  rb_stts_size * trans->num_rx_queues,
				  trans_pcie->base_rb_stts,
				  trans_pcie->base_rb_stts_dma);
		trans_pcie->base_rb_stts = NULL;
		trans_pcie->base_rb_stts_dma = 0;
	}

	for (i = 0; i < trans->num_rx_queues; i++) {
		struct iwl_rxq *rxq = &trans_pcie->rxq[i];

		iwl_pcie_free_rxq_dma(trans, rxq);

		if (rxq->napi.poll)
			netif_napi_del(&rxq->napi);
	}
	kfree(trans_pcie->rxq);
}