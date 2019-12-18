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
struct TYPE_4__ {TYPE_1__* wks; } ;
struct iwl_fw_runtime {TYPE_2__ dump; int /*<<< orphan*/  trans; } ;
struct TYPE_3__ {int /*<<< orphan*/  ini_trig_id; int /*<<< orphan*/  wk; } ;

/* Variables and functions */
 int IWL_FW_RUNTIME_DUMP_WK_NUM ; 
 int /*<<< orphan*/  IWL_FW_TRIGGER_ID_INVALID ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_del_timers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_fw_flush_dumps(struct iwl_fw_runtime *fwrt)
{
	int i;

	iwl_dbg_tlv_del_timers(fwrt->trans);
	for (i = 0; i < IWL_FW_RUNTIME_DUMP_WK_NUM; i++) {
		flush_delayed_work(&fwrt->dump.wks[i].wk);
		fwrt->dump.wks[i].ini_trig_id = IWL_FW_TRIGGER_ID_INVALID;
	}
}