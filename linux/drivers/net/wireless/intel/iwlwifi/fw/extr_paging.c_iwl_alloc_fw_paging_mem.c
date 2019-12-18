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
struct page {int dummy; } ;
struct iwl_fw_runtime {int num_of_paging_blk; int num_of_pages_in_last_blk; TYPE_2__* fw_paging_db; TYPE_1__* trans; } ;
struct fw_img {int paging_mem_size; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int fw_paging_size; int /*<<< orphan*/  fw_paging_phys; struct page* fw_paging_block; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOCK_2_EXP_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int FW_PAGING_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_fw_runtime*,char*,int,...) ; 
 int NUM_OF_PAGE_PER_GROUP ; 
 int PAGE_SIZE ; 
 int PAGING_BLOCK_SIZE ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  iwl_free_fw_paging (struct iwl_fw_runtime*) ; 

__attribute__((used)) static int iwl_alloc_fw_paging_mem(struct iwl_fw_runtime *fwrt,
				   const struct fw_img *image)
{
	struct page *block;
	dma_addr_t phys = 0;
	int blk_idx, order, num_of_pages, size;

	if (fwrt->fw_paging_db[0].fw_paging_block)
		return 0;

	/* ensure BLOCK_2_EXP_SIZE is power of 2 of PAGING_BLOCK_SIZE */
	BUILD_BUG_ON(BIT(BLOCK_2_EXP_SIZE) != PAGING_BLOCK_SIZE);

	num_of_pages = image->paging_mem_size / FW_PAGING_SIZE;
	fwrt->num_of_paging_blk =
		DIV_ROUND_UP(num_of_pages, NUM_OF_PAGE_PER_GROUP);
	fwrt->num_of_pages_in_last_blk =
		num_of_pages -
		NUM_OF_PAGE_PER_GROUP * (fwrt->num_of_paging_blk - 1);

	IWL_DEBUG_FW(fwrt,
		     "Paging: allocating mem for %d paging blocks, each block holds 8 pages, last block holds %d pages\n",
		     fwrt->num_of_paging_blk,
		     fwrt->num_of_pages_in_last_blk);

	/*
	 * Allocate CSS and paging blocks in dram.
	 */
	for (blk_idx = 0; blk_idx < fwrt->num_of_paging_blk + 1; blk_idx++) {
		/* For CSS allocate 4KB, for others PAGING_BLOCK_SIZE (32K) */
		size = blk_idx ? PAGING_BLOCK_SIZE : FW_PAGING_SIZE;
		order = get_order(size);
		block = alloc_pages(GFP_KERNEL, order);
		if (!block) {
			/* free all the previous pages since we failed */
			iwl_free_fw_paging(fwrt);
			return -ENOMEM;
		}

		fwrt->fw_paging_db[blk_idx].fw_paging_block = block;
		fwrt->fw_paging_db[blk_idx].fw_paging_size = size;

		phys = dma_map_page(fwrt->trans->dev, block, 0,
				    PAGE_SIZE << order,
				    DMA_BIDIRECTIONAL);
		if (dma_mapping_error(fwrt->trans->dev, phys)) {
			/*
			 * free the previous pages and the current one
			 * since we failed to map_page.
			 */
			iwl_free_fw_paging(fwrt);
			return -ENOMEM;
		}
		fwrt->fw_paging_db[blk_idx].fw_paging_phys = phys;

		if (!blk_idx)
			IWL_DEBUG_FW(fwrt,
				     "Paging: allocated 4K(CSS) bytes (order %d) for firmware paging.\n",
				     order);
		else
			IWL_DEBUG_FW(fwrt,
				     "Paging: allocated 32K bytes (order %d) for firmware paging.\n",
				     order);
	}

	return 0;
}