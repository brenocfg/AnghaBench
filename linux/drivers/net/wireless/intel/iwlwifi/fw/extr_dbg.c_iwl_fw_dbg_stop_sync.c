#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iwl_fw_runtime {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int IWL_FW_RUNTIME_DUMP_WK_NUM ; 
 int /*<<< orphan*/  iwl_dbg_tlv_del_timers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_sync (struct iwl_fw_runtime*,int) ; 
 int /*<<< orphan*/  iwl_fw_dbg_stop_restart_recording (struct iwl_fw_runtime*,int /*<<< orphan*/ *,int) ; 

void iwl_fw_dbg_stop_sync(struct iwl_fw_runtime *fwrt)
{
	int i;

	iwl_dbg_tlv_del_timers(fwrt->trans);
	for (i = 0; i < IWL_FW_RUNTIME_DUMP_WK_NUM; i++)
		iwl_fw_dbg_collect_sync(fwrt, i);

	iwl_fw_dbg_stop_restart_recording(fwrt, NULL, true);
}