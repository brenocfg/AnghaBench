#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iwl_fw_runtime {TYPE_3__* trans; TYPE_1__* fw; } ;
struct iwl_fw_dbg_params {int dummy; } ;
struct TYPE_7__ {scalar_t__ ini_dest; int rec_on; int /*<<< orphan*/  dest_tlv; } ;
struct TYPE_8__ {TYPE_2__ dbg; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 scalar_t__ IWL_FW_INI_LOCATION_INVALID ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_DBG_SUSPEND_RESUME_CMD_SUPP ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_fw_dbg_restart_recording (TYPE_3__*,struct iwl_fw_dbg_params*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_stop_recording (TYPE_3__*,struct iwl_fw_dbg_params*) ; 
 int iwl_fw_dbg_suspend_resume_hcmd (TYPE_3__*,int) ; 
 int /*<<< orphan*/  iwl_fw_set_dbg_rec_on (struct iwl_fw_runtime*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_fw_dbg_stop_restart_recording(struct iwl_fw_runtime *fwrt,
				      struct iwl_fw_dbg_params *params,
				      bool stop)
{
	int ret = 0;

	/* if the FW crashed or not debug monitor cfg was given, there is
	 * no point in changing the recording state
	 */
	if (test_bit(STATUS_FW_ERROR, &fwrt->trans->status) ||
	    (!fwrt->trans->dbg.dest_tlv &&
	     fwrt->trans->dbg.ini_dest == IWL_FW_INI_LOCATION_INVALID))
		return 0;

	if (fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_DBG_SUSPEND_RESUME_CMD_SUPP))
		ret = iwl_fw_dbg_suspend_resume_hcmd(fwrt->trans, stop);
	else if (stop)
		iwl_fw_dbg_stop_recording(fwrt->trans, params);
	else
		ret = iwl_fw_dbg_restart_recording(fwrt->trans, params);
#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (!ret) {
		if (stop)
			fwrt->trans->dbg.rec_on = false;
		else
			iwl_fw_set_dbg_rec_on(fwrt);
	}
#endif

	return ret;
}