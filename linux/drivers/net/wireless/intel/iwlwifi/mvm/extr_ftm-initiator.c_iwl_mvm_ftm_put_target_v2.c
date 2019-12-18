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
struct iwl_tof_range_req_ap_entry_v2 {int /*<<< orphan*/  algo_type; int /*<<< orphan*/  location_req; int /*<<< orphan*/  enable_dyn_ack; int /*<<< orphan*/  asap_mode; int /*<<< orphan*/  retries_per_sample; scalar_t__ measure_type; int /*<<< orphan*/  num_of_bursts; int /*<<< orphan*/  samples_per_burst; int /*<<< orphan*/  burst_period; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ctrl_ch_position; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  channel_num; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {scalar_t__ request_civicloc; scalar_t__ request_lci; int /*<<< orphan*/  asap; int /*<<< orphan*/  ftmr_retries; int /*<<< orphan*/  num_bursts_exp; int /*<<< orphan*/  ftms_per_burst; int /*<<< orphan*/  burst_period; } ;
struct cfg80211_pmsr_request_peer {TYPE_1__ ftm; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IWL_MVM_FTM_INITIATOR_ALGO ; 
 int /*<<< orphan*/  IWL_MVM_FTM_INITIATOR_DYNACK ; 
 int /*<<< orphan*/  IWL_TOF_LOC_CIVIC ; 
 int /*<<< orphan*/  IWL_TOF_LOC_LCI ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_ftm_target_chandef (struct iwl_mvm*,struct cfg80211_pmsr_request_peer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwl_mvm_ftm_put_target_v2(struct iwl_mvm *mvm,
			  struct cfg80211_pmsr_request_peer *peer,
			  struct iwl_tof_range_req_ap_entry_v2 *target)
{
	int ret;

	ret = iwl_mvm_ftm_target_chandef(mvm, peer, &target->channel_num,
					 &target->bandwidth,
					 &target->ctrl_ch_position);
	if (ret)
		return ret;

	memcpy(target->bssid, peer->addr, ETH_ALEN);
	target->burst_period =
		cpu_to_le16(peer->ftm.burst_period);
	target->samples_per_burst = peer->ftm.ftms_per_burst;
	target->num_of_bursts = peer->ftm.num_bursts_exp;
	target->measure_type = 0; /* regular two-sided FTM */
	target->retries_per_sample = peer->ftm.ftmr_retries;
	target->asap_mode = peer->ftm.asap;
	target->enable_dyn_ack = IWL_MVM_FTM_INITIATOR_DYNACK;

	if (peer->ftm.request_lci)
		target->location_req |= IWL_TOF_LOC_LCI;
	if (peer->ftm.request_civicloc)
		target->location_req |= IWL_TOF_LOC_CIVIC;

	target->algo_type = IWL_MVM_FTM_INITIATOR_ALGO;

	return 0;
}