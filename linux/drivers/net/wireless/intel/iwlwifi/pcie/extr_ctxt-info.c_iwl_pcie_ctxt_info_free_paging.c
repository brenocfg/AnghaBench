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
struct iwl_self_init_dram {int paging_cnt; TYPE_1__* paging; } ;
struct iwl_trans {int /*<<< orphan*/  dev; struct iwl_self_init_dram init_dram; } ;
struct TYPE_2__ {int /*<<< orphan*/  physical; int /*<<< orphan*/  block; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void iwl_pcie_ctxt_info_free_paging(struct iwl_trans *trans)
{
	struct iwl_self_init_dram *dram = &trans->init_dram;
	int i;

	if (!dram->paging) {
		WARN_ON(dram->paging_cnt);
		return;
	}

	/* free paging*/
	for (i = 0; i < dram->paging_cnt; i++)
		dma_free_coherent(trans->dev, dram->paging[i].size,
				  dram->paging[i].block,
				  dram->paging[i].physical);

	kfree(dram->paging);
	dram->paging_cnt = 0;
	dram->paging = NULL;
}