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
struct iwl_rb_allocator {int /*<<< orphan*/  lock; } ;
struct iwl_trans_pcie {struct iwl_rxq* rxq; scalar_t__ base_rb_stts_dma; int /*<<< orphan*/ * base_rb_stts; struct iwl_rb_allocator rba; } ;
struct iwl_trans {size_t num_rx_queues; int /*<<< orphan*/  dev; TYPE_1__* trans_cfg; } ;
struct iwl_rxq {int id; } ;
struct iwl_rb_status {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ WARN_ON (struct iwl_rxq*) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,scalar_t__) ; 
 int iwl_pcie_alloc_rxq_dma (struct iwl_trans*,struct iwl_rxq*) ; 
 struct iwl_rxq* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iwl_rxq*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int iwl_pcie_rx_alloc(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rb_allocator *rba = &trans_pcie->rba;
	int i, ret;
	size_t rb_stts_size = trans->trans_cfg->device_family >=
			      IWL_DEVICE_FAMILY_22560 ?
			      sizeof(__le16) : sizeof(struct iwl_rb_status);

	if (WARN_ON(trans_pcie->rxq))
		return -EINVAL;

	trans_pcie->rxq = kcalloc(trans->num_rx_queues, sizeof(struct iwl_rxq),
				  GFP_KERNEL);
	if (!trans_pcie->rxq)
		return -ENOMEM;

	spin_lock_init(&rba->lock);

	/*
	 * Allocate the driver's pointer to receive buffer status.
	 * Allocate for all queues continuously (HW requirement).
	 */
	trans_pcie->base_rb_stts =
			dma_alloc_coherent(trans->dev,
					   rb_stts_size * trans->num_rx_queues,
					   &trans_pcie->base_rb_stts_dma,
					   GFP_KERNEL);
	if (!trans_pcie->base_rb_stts) {
		ret = -ENOMEM;
		goto err;
	}

	for (i = 0; i < trans->num_rx_queues; i++) {
		struct iwl_rxq *rxq = &trans_pcie->rxq[i];

		rxq->id = i;
		ret = iwl_pcie_alloc_rxq_dma(trans, rxq);
		if (ret)
			goto err;
	}
	return 0;

err:
	if (trans_pcie->base_rb_stts) {
		dma_free_coherent(trans->dev,
				  rb_stts_size * trans->num_rx_queues,
				  trans_pcie->base_rb_stts,
				  trans_pcie->base_rb_stts_dma);
		trans_pcie->base_rb_stts = NULL;
		trans_pcie->base_rb_stts_dma = 0;
	}
	kfree(trans_pcie->rxq);

	return ret;
}