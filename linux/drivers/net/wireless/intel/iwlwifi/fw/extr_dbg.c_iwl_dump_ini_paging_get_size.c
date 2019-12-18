#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_fw_runtime {TYPE_3__* fw_paging_db; TYPE_5__* trans; } ;
struct iwl_fw_ini_region_cfg {int dummy; } ;
struct iwl_fw_ini_error_dump_range {int dummy; } ;
struct iwl_fw_ini_error_dump {int dummy; } ;
struct TYPE_7__ {TYPE_1__* paging; } ;
struct TYPE_10__ {TYPE_2__ init_dram; TYPE_4__* trans_cfg; } ;
struct TYPE_9__ {scalar_t__ gen2; } ;
struct TYPE_8__ {int fw_paging_size; } ;
struct TYPE_6__ {int size; } ;

/* Variables and functions */
 int iwl_dump_ini_paging_ranges (struct iwl_fw_runtime*,struct iwl_fw_ini_region_cfg*) ; 

__attribute__((used)) static u32 iwl_dump_ini_paging_get_size(struct iwl_fw_runtime *fwrt,
					struct iwl_fw_ini_region_cfg *reg)
{
	int i;
	u32 range_header_len = sizeof(struct iwl_fw_ini_error_dump_range);
	u32 size = sizeof(struct iwl_fw_ini_error_dump);

	if (fwrt->trans->trans_cfg->gen2) {
		for (i = 0; i < iwl_dump_ini_paging_ranges(fwrt, reg); i++)
			size += range_header_len +
				fwrt->trans->init_dram.paging[i].size;
	} else {
		for (i = 1; i <= iwl_dump_ini_paging_ranges(fwrt, reg); i++)
			size += range_header_len +
				fwrt->fw_paging_db[i].fw_paging_size;
	}

	return size;
}