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
struct iwl_txq {int dummy; } ;
struct iwl_trans_pcie {int max_tbs; } ;
struct iwl_trans {TYPE_1__* trans_cfg; int /*<<< orphan*/  dev; } ;
struct iwl_tfh_tfd {scalar_t__ num_tbs; } ;
struct iwl_tfd {scalar_t__ num_tbs; } ;
struct iwl_cmd_meta {int tbs; } ;
struct TYPE_2__ {scalar_t__ use_tfh; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* iwl_pcie_get_tfd (struct iwl_trans*,struct iwl_txq*,int) ; 
 int iwl_pcie_tfd_get_num_tbs (struct iwl_trans*,void*) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_tb_get_addr (struct iwl_trans*,void*,int) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_tb_get_len (struct iwl_trans*,void*,int) ; 

__attribute__((used)) static void iwl_pcie_tfd_unmap(struct iwl_trans *trans,
			       struct iwl_cmd_meta *meta,
			       struct iwl_txq *txq, int index)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int i, num_tbs;
	void *tfd = iwl_pcie_get_tfd(trans, txq, index);

	/* Sanity check on number of chunks */
	num_tbs = iwl_pcie_tfd_get_num_tbs(trans, tfd);

	if (num_tbs > trans_pcie->max_tbs) {
		IWL_ERR(trans, "Too many chunks: %i\n", num_tbs);
		/* @todo issue fatal error, it is quite serious situation */
		return;
	}

	/* first TB is never freed - it's the bidirectional DMA data */

	for (i = 1; i < num_tbs; i++) {
		if (meta->tbs & BIT(i))
			dma_unmap_page(trans->dev,
				       iwl_pcie_tfd_tb_get_addr(trans, tfd, i),
				       iwl_pcie_tfd_tb_get_len(trans, tfd, i),
				       DMA_TO_DEVICE);
		else
			dma_unmap_single(trans->dev,
					 iwl_pcie_tfd_tb_get_addr(trans, tfd,
								  i),
					 iwl_pcie_tfd_tb_get_len(trans, tfd,
								 i),
					 DMA_TO_DEVICE);
	}

	meta->tbs = 0;

	if (trans->trans_cfg->use_tfh) {
		struct iwl_tfh_tfd *tfd_fh = (void *)tfd;

		tfd_fh->num_tbs = 0;
	} else {
		struct iwl_tfd *tfd_fh = (void *)tfd;

		tfd_fh->num_tbs = 0;
	}

}