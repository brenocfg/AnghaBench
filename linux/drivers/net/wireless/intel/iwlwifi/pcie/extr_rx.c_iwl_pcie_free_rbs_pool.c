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
struct iwl_trans_pcie {int rx_page_order; TYPE_1__* rx_pool; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * page; int /*<<< orphan*/  page_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int PAGE_SIZE ; 
 int RX_POOL_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void iwl_pcie_free_rbs_pool(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int i;

	for (i = 0; i < RX_POOL_SIZE; i++) {
		if (!trans_pcie->rx_pool[i].page)
			continue;
		dma_unmap_page(trans->dev, trans_pcie->rx_pool[i].page_dma,
			       PAGE_SIZE << trans_pcie->rx_page_order,
			       DMA_FROM_DEVICE);
		__free_pages(trans_pcie->rx_pool[i].page,
			     trans_pcie->rx_page_order);
		trans_pcie->rx_pool[i].page = NULL;
	}
}