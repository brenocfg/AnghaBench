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
struct iwl_trans_pcie {int max_tbs; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
struct iwl_tfh_tfd {int /*<<< orphan*/  num_tbs; TYPE_1__* tbs; } ;
struct iwl_cmd_meta {int tbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tb_len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_pcie_gen2_get_num_tbs (struct iwl_trans*,struct iwl_tfh_tfd*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_pcie_gen2_tfd_unmap(struct iwl_trans *trans,
				    struct iwl_cmd_meta *meta,
				    struct iwl_tfh_tfd *tfd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int i, num_tbs;

	/* Sanity check on number of chunks */
	num_tbs = iwl_pcie_gen2_get_num_tbs(trans, tfd);

	if (num_tbs > trans_pcie->max_tbs) {
		IWL_ERR(trans, "Too many chunks: %i\n", num_tbs);
		return;
	}

	/* first TB is never freed - it's the bidirectional DMA data */
	for (i = 1; i < num_tbs; i++) {
		if (meta->tbs & BIT(i))
			dma_unmap_page(trans->dev,
				       le64_to_cpu(tfd->tbs[i].addr),
				       le16_to_cpu(tfd->tbs[i].tb_len),
				       DMA_TO_DEVICE);
		else
			dma_unmap_single(trans->dev,
					 le64_to_cpu(tfd->tbs[i].addr),
					 le16_to_cpu(tfd->tbs[i].tb_len),
					 DMA_TO_DEVICE);
	}

	tfd->num_tbs = 0;
}