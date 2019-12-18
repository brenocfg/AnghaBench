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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_trans_txq_scd_cfg {int /*<<< orphan*/  fifo; int /*<<< orphan*/  tid; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  aggregate; int /*<<< orphan*/  frame_limit; } ;
struct iwl_scd_txq_cfg_cmd {int scd_queue; int /*<<< orphan*/  ssn; int /*<<< orphan*/  tid; int /*<<< orphan*/  aggregate; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  window; int /*<<< orphan*/  action; } ;
struct iwl_mvm {int /*<<< orphan*/  trans; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  SCD_CFG_ENABLE_QUEUE ; 
 int /*<<< orphan*/  SCD_QUEUE_CFG ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_scd_txq_cfg_cmd*) ; 
 int /*<<< orphan*/  iwl_mvm_update_txq_mapping (struct iwl_mvm*,struct ieee80211_sta*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_trans_txq_enable_cfg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool iwl_mvm_enable_txq(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			       int queue, u16 ssn,
			       const struct iwl_trans_txq_scd_cfg *cfg,
			       unsigned int wdg_timeout)
{
	struct iwl_scd_txq_cfg_cmd cmd = {
		.scd_queue = queue,
		.action = SCD_CFG_ENABLE_QUEUE,
		.window = cfg->frame_limit,
		.sta_id = cfg->sta_id,
		.ssn = cpu_to_le16(ssn),
		.tx_fifo = cfg->fifo,
		.aggregate = cfg->aggregate,
		.tid = cfg->tid,
	};
	bool inc_ssn;

	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return false;

	/* Send the enabling command if we need to */
	if (!iwl_mvm_update_txq_mapping(mvm, sta, queue, cfg->sta_id, cfg->tid))
		return false;

	inc_ssn = iwl_trans_txq_enable_cfg(mvm->trans, queue, ssn,
					   NULL, wdg_timeout);
	if (inc_ssn)
		le16_add_cpu(&cmd.ssn, 1);

	WARN(iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, 0, sizeof(cmd), &cmd),
	     "Failed to configure queue %d on FIFO %d\n", queue, cfg->fifo);

	return inc_ssn;
}