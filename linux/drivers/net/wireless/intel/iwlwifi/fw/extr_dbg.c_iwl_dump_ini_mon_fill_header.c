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
typedef  int u32 ;
struct iwl_fw_runtime {int /*<<< orphan*/  trans; } ;
struct iwl_fw_ini_region_cfg {int dummy; } ;
struct TYPE_2__ {void* version; } ;
struct iwl_fw_ini_monitor_dump {void* ranges; void* cycle_cnt; void* write_ptr; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_fw_runtime*,char*) ; 
 int IWL_INI_DUMP_VER ; 
 void* cpu_to_le32 (int) ; 
 int iwl_read_prph_no_grab (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void
*iwl_dump_ini_mon_fill_header(struct iwl_fw_runtime *fwrt,
			      struct iwl_fw_ini_region_cfg *reg,
			      struct iwl_fw_ini_monitor_dump *data,
			      u32 write_ptr_addr, u32 write_ptr_msk,
			      u32 cycle_cnt_addr, u32 cycle_cnt_msk)
{
	u32 write_ptr, cycle_cnt;
	unsigned long flags;

	if (!iwl_trans_grab_nic_access(fwrt->trans, &flags)) {
		IWL_ERR(fwrt, "Failed to get monitor header\n");
		return NULL;
	}

	write_ptr = iwl_read_prph_no_grab(fwrt->trans, write_ptr_addr);
	cycle_cnt = iwl_read_prph_no_grab(fwrt->trans, cycle_cnt_addr);

	iwl_trans_release_nic_access(fwrt->trans, &flags);

	data->header.version = cpu_to_le32(IWL_INI_DUMP_VER);
	data->write_ptr = cpu_to_le32(write_ptr & write_ptr_msk);
	data->cycle_cnt = cpu_to_le32(cycle_cnt & cycle_cnt_msk);

	return data->ranges;
}