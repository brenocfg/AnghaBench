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
struct TYPE_3__ {scalar_t__ group_id; int /*<<< orphan*/  cmd; } ;
struct iwl_rx_packet {TYPE_1__ hdr; } ;
struct iwl_mvm {int /*<<< orphan*/  fwrt; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_cmd {TYPE_2__* cmds; } ;
struct TYPE_4__ {scalar_t__ group_id; int /*<<< orphan*/  cmd_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_FW_NOTIF ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_trigger_on (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_mvm_rx_check_trigger(struct iwl_mvm *mvm,
					    struct iwl_rx_packet *pkt)
{
	struct iwl_fw_dbg_trigger_tlv *trig;
	struct iwl_fw_dbg_trigger_cmd *cmds_trig;
	int i;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, NULL,
				     FW_DBG_TRIGGER_FW_NOTIF);
	if (!trig)
		return;

	cmds_trig = (void *)trig->data;

	for (i = 0; i < ARRAY_SIZE(cmds_trig->cmds); i++) {
		/* don't collect on CMD 0 */
		if (!cmds_trig->cmds[i].cmd_id)
			break;

		if (cmds_trig->cmds[i].cmd_id != pkt->hdr.cmd ||
		    cmds_trig->cmds[i].group_id != pkt->hdr.group_id)
			continue;

		iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
					"CMD 0x%02x.%02x received",
					pkt->hdr.group_id, pkt->hdr.cmd);
		break;
	}
}