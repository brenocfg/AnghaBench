#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct iwl_wowlan_config_cmd {int /*<<< orphan*/ * qos_seq; } ;
struct iwl_mvm_sta {TYPE_1__* tid_data; } ;
struct TYPE_2__ {int seq_number; } ;

/* Variables and functions */
 int IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

void iwl_mvm_set_wowlan_qos_seq(struct iwl_mvm_sta *mvm_ap_sta,
				struct iwl_wowlan_config_cmd *cmd)
{
	int i;

	/*
	 * For QoS counters, we store the one to use next, so subtract 0x10
	 * since the uCode will add 0x10 *before* using the value while we
	 * increment after using the value (i.e. store the next value to use).
	 */
	for (i = 0; i < IWL_MAX_TID_COUNT; i++) {
		u16 seq = mvm_ap_sta->tid_data[i].seq_number;
		seq -= 0x10;
		cmd->qos_seq[i] = cpu_to_le16(seq);
	}
}