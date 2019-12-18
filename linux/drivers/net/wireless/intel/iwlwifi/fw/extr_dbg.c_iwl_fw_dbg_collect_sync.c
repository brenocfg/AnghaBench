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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  active_wks; } ;
struct iwl_fw_runtime {TYPE_2__ dump; TYPE_3__* trans; int /*<<< orphan*/  ops_ctx; TYPE_1__* ops; } ;
struct iwl_fw_dbg_params {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fw_running ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_FW_INFO (struct iwl_fw_runtime*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_fw_runtime*,char*) ; 
 int /*<<< orphan*/  STATUS_TRANS_DEAD ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_fw_dbg_stop_restart_recording (struct iwl_fw_runtime*,struct iwl_fw_dbg_params*,int) ; 
 int /*<<< orphan*/  iwl_fw_error_dump (struct iwl_fw_runtime*) ; 
 int /*<<< orphan*/  iwl_fw_error_ini_dump (struct iwl_fw_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_free_dump_desc (struct iwl_fw_runtime*) ; 
 scalar_t__ iwl_trans_dbg_ini_valid (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_fw_dbg_collect_sync(struct iwl_fw_runtime *fwrt, u8 wk_idx)
{
	struct iwl_fw_dbg_params params = {0};

	if (!test_bit(wk_idx, &fwrt->dump.active_wks))
		return;

	if (fwrt->ops && fwrt->ops->fw_running &&
	    !fwrt->ops->fw_running(fwrt->ops_ctx)) {
		IWL_ERR(fwrt, "Firmware not running - cannot dump error\n");
		iwl_fw_free_dump_desc(fwrt);
		goto out;
	}

	/* there's no point in fw dump if the bus is dead */
	if (test_bit(STATUS_TRANS_DEAD, &fwrt->trans->status)) {
		IWL_ERR(fwrt, "Skip fw error dump since bus is dead\n");
		goto out;
	}

	if (iwl_fw_dbg_stop_restart_recording(fwrt, &params, true)) {
		IWL_ERR(fwrt, "Failed to stop DBGC recording, aborting dump\n");
		goto out;
	}

	IWL_DEBUG_FW_INFO(fwrt, "WRT: Data collection start\n");
	if (iwl_trans_dbg_ini_valid(fwrt->trans))
		iwl_fw_error_ini_dump(fwrt, wk_idx);
	else
		iwl_fw_error_dump(fwrt);
	IWL_DEBUG_FW_INFO(fwrt, "WRT: Data collection done\n");

	iwl_fw_dbg_stop_restart_recording(fwrt, &params, false);

out:
	clear_bit(wk_idx, &fwrt->dump.active_wks);
}