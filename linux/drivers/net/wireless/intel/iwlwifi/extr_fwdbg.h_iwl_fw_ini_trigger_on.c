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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {TYPE_2__* active_trigs; } ;
struct iwl_fw_runtime {TYPE_1__ dump; int /*<<< orphan*/  trans; } ;
struct iwl_fw_ini_trigger {int /*<<< orphan*/  ignore_consec; } ;
typedef  enum iwl_fw_ini_trigger_id { ____Placeholder_iwl_fw_ini_trigger_id } iwl_fw_ini_trigger_id ;
struct TYPE_4__ {struct iwl_fw_ini_trigger* trig; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int IWL_FW_TRIGGER_ID_INVALID ; 
 int IWL_FW_TRIGGER_ID_NUM ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_fw_runtime*,char*,int) ; 
 scalar_t__ iwl_fw_dbg_no_trig_window (struct iwl_fw_runtime*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_dbg_ini_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
iwl_fw_ini_trigger_on(struct iwl_fw_runtime *fwrt,
		      enum iwl_fw_ini_trigger_id id)
{
	struct iwl_fw_ini_trigger *trig;
	u32 usec;

	if (!iwl_trans_dbg_ini_valid(fwrt->trans) ||
	    id == IWL_FW_TRIGGER_ID_INVALID || id >= IWL_FW_TRIGGER_ID_NUM ||
	    !fwrt->dump.active_trigs[id].active)
		return false;

	trig = fwrt->dump.active_trigs[id].trig;
	usec = le32_to_cpu(trig->ignore_consec);

	if (iwl_fw_dbg_no_trig_window(fwrt, id, usec)) {
		IWL_WARN(fwrt, "Trigger %d fired in no-collect window\n", id);
		return false;
	}

	return true;
}