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
struct TYPE_4__ {TYPE_1__* wks; struct iwl_fw_ini_active_triggers* active_trigs; int /*<<< orphan*/ * d3_debug_data; } ;
struct iwl_fw_runtime {TYPE_2__ dump; int /*<<< orphan*/  trans; } ;
struct iwl_fw_ini_active_triggers {int active; int /*<<< orphan*/ * trig; scalar_t__ size; } ;
struct TYPE_3__ {int /*<<< orphan*/  wk; } ;

/* Variables and functions */
 int IWL_FW_RUNTIME_DUMP_WK_NUM ; 
 int IWL_FW_TRIGGER_ID_NUM ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_del_timers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iwl_fw_runtime_free(struct iwl_fw_runtime *fwrt)
{
	int i;

	kfree(fwrt->dump.d3_debug_data);
	fwrt->dump.d3_debug_data = NULL;

	for (i = 0; i < IWL_FW_TRIGGER_ID_NUM; i++) {
		struct iwl_fw_ini_active_triggers *active =
			&fwrt->dump.active_trigs[i];

		active->active = false;
		active->size = 0;
		kfree(active->trig);
		active->trig = NULL;
	}

	iwl_dbg_tlv_del_timers(fwrt->trans);
	for (i = 0; i < IWL_FW_RUNTIME_DUMP_WK_NUM; i++)
		cancel_delayed_work_sync(&fwrt->dump.wks[i].wk);
}