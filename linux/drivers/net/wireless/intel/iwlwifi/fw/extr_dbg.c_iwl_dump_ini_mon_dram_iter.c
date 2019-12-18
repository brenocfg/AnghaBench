#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_fw_runtime {TYPE_3__* trans; } ;
struct iwl_fw_ini_region_cfg {int dummy; } ;
struct iwl_fw_ini_error_dump_range {int /*<<< orphan*/  range_data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  dram_base_addr; } ;
struct TYPE_5__ {TYPE_1__* fw_mon; } ;
struct TYPE_6__ {TYPE_2__ dbg; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MON_BUFF_BASE_ADDR_VER2 ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int iwl_read_umac_prph (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwl_dump_ini_mon_dram_iter(struct iwl_fw_runtime *fwrt,
			   struct iwl_fw_ini_region_cfg *reg, void *range_ptr,
			   int idx)
{
	struct iwl_fw_ini_error_dump_range *range = range_ptr;
	u32 start_addr = iwl_read_umac_prph(fwrt->trans,
					    MON_BUFF_BASE_ADDR_VER2);

	if (start_addr == 0x5a5a5a5a)
		return -EBUSY;

	range->dram_base_addr = cpu_to_le64(start_addr);
	range->range_data_size = cpu_to_le32(fwrt->trans->dbg.fw_mon[idx].size);

	memcpy(range->data, fwrt->trans->dbg.fw_mon[idx].block,
	       fwrt->trans->dbg.fw_mon[idx].size);

	return sizeof(*range) + le32_to_cpu(range->range_data_size);
}