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
struct iwl_fw_runtime {TYPE_2__* trans; } ;
struct iwl_fw_ini_region_cfg {int dummy; } ;
struct iwl_fw_ini_monitor_dump {int dummy; } ;
struct TYPE_4__ {TYPE_1__* trans_cfg; } ;
struct TYPE_3__ {int device_family; } ;

/* Variables and functions */
#define  IWL_DEVICE_FAMILY_22000 129 
#define  IWL_DEVICE_FAMILY_9000 128 
 int /*<<< orphan*/  IWL_ERR (struct iwl_fw_runtime*,char*,int) ; 
 int MON_BUFF_CYCLE_CNT_VER2 ; 
 int MON_BUFF_WRPTR_VER2 ; 
 void* iwl_dump_ini_mon_fill_header (struct iwl_fw_runtime*,struct iwl_fw_ini_region_cfg*,struct iwl_fw_ini_monitor_dump*,int,int,int,int) ; 

__attribute__((used)) static void
*iwl_dump_ini_mon_dram_fill_header(struct iwl_fw_runtime *fwrt,
				   struct iwl_fw_ini_region_cfg *reg,
				   void *data)
{
	struct iwl_fw_ini_monitor_dump *mon_dump = (void *)data;
	u32 write_ptr_addr, write_ptr_msk, cycle_cnt_addr, cycle_cnt_msk;

	switch (fwrt->trans->trans_cfg->device_family) {
	case IWL_DEVICE_FAMILY_9000:
	case IWL_DEVICE_FAMILY_22000:
		write_ptr_addr = MON_BUFF_WRPTR_VER2;
		write_ptr_msk = -1;
		cycle_cnt_addr = MON_BUFF_CYCLE_CNT_VER2;
		cycle_cnt_msk = -1;
		break;
	default:
		IWL_ERR(fwrt, "Unsupported device family %d\n",
			fwrt->trans->trans_cfg->device_family);
		return NULL;
	}

	return iwl_dump_ini_mon_fill_header(fwrt, reg, mon_dump, write_ptr_addr,
					    write_ptr_msk, cycle_cnt_addr,
					    cycle_cnt_msk);
}