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
typedef  scalar_t__ u32 ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_mvm {int /*<<< orphan*/  fwrt; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_stats {int /*<<< orphan*/  stop_threshold; int /*<<< orphan*/  stop_offset; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DBG_TRIGGER_STATS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,int /*<<< orphan*/ *) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_trigger_on (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
iwl_mvm_rx_stats_check_trigger(struct iwl_mvm *mvm, struct iwl_rx_packet *pkt)
{
	struct iwl_fw_dbg_trigger_tlv *trig;
	struct iwl_fw_dbg_trigger_stats *trig_stats;
	u32 trig_offset, trig_thold;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, NULL, FW_DBG_TRIGGER_STATS);
	if (!trig)
		return;

	trig_stats = (void *)trig->data;

	trig_offset = le32_to_cpu(trig_stats->stop_offset);
	trig_thold = le32_to_cpu(trig_stats->stop_threshold);

	if (WARN_ON_ONCE(trig_offset >= iwl_rx_packet_payload_len(pkt)))
		return;

	if (le32_to_cpup((__le32 *) (pkt->data + trig_offset)) < trig_thold)
		return;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig, NULL);
}