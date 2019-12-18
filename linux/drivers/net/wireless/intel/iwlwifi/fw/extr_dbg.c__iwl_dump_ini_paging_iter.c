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
typedef  int u32 ;
struct page {int dummy; } ;
struct iwl_fw_runtime {TYPE_2__* trans; TYPE_1__* fw_paging_db; } ;
struct iwl_fw_ini_region_cfg {int dummy; } ;
struct iwl_fw_ini_error_dump_range {void* range_data_size; int /*<<< orphan*/  data; void* page_num; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int fw_paging_size; int /*<<< orphan*/  fw_paging_phys; struct page* fw_paging_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static int _iwl_dump_ini_paging_iter(struct iwl_fw_runtime *fwrt,
				     struct iwl_fw_ini_region_cfg *reg,
				     void *range_ptr, int idx)
{
	/* increase idx by 1 since the pages are from 1 to
	 * fwrt->num_of_paging_blk + 1
	 */
	struct page *page = fwrt->fw_paging_db[++idx].fw_paging_block;
	struct iwl_fw_ini_error_dump_range *range = range_ptr;
	dma_addr_t addr = fwrt->fw_paging_db[idx].fw_paging_phys;
	u32 page_size = fwrt->fw_paging_db[idx].fw_paging_size;

	range->page_num = cpu_to_le32(idx);
	range->range_data_size = cpu_to_le32(page_size);
	dma_sync_single_for_cpu(fwrt->trans->dev, addr,	page_size,
				DMA_BIDIRECTIONAL);
	memcpy(range->data, page_address(page), page_size);
	dma_sync_single_for_device(fwrt->trans->dev, addr, page_size,
				   DMA_BIDIRECTIONAL);

	return sizeof(*range) + le32_to_cpu(range->range_data_size);
}