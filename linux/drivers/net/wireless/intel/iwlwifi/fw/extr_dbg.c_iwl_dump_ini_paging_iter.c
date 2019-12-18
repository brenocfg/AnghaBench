#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_fw_runtime {TYPE_3__* trans; } ;
struct iwl_fw_ini_region_cfg {int dummy; } ;
struct iwl_fw_ini_error_dump_range {void* range_data_size; int /*<<< orphan*/  data; void* page_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  gen2; } ;
struct TYPE_6__ {TYPE_1__* paging; } ;
struct TYPE_7__ {TYPE_2__ init_dram; TYPE_4__* trans_cfg; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int _iwl_dump_ini_paging_iter (struct iwl_fw_runtime*,struct iwl_fw_ini_region_cfg*,void*,int) ; 
 void* cpu_to_le32 (int) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_dump_ini_paging_iter(struct iwl_fw_runtime *fwrt,
				    struct iwl_fw_ini_region_cfg *reg,
				    void *range_ptr, int idx)
{
	struct iwl_fw_ini_error_dump_range *range;
	u32 page_size;

	if (!fwrt->trans->trans_cfg->gen2)
		return _iwl_dump_ini_paging_iter(fwrt, reg, range_ptr, idx);

	range = range_ptr;
	page_size = fwrt->trans->init_dram.paging[idx].size;

	range->page_num = cpu_to_le32(idx);
	range->range_data_size = cpu_to_le32(page_size);
	memcpy(range->data, fwrt->trans->init_dram.paging[idx].block,
	       page_size);

	return sizeof(*range) + le32_to_cpu(range->range_data_size);
}