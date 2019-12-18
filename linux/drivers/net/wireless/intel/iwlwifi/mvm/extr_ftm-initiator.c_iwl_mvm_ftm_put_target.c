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
struct iwl_tof_range_req_ap_entry {int /*<<< orphan*/  initiator_ap_flags; int /*<<< orphan*/  ftmr_max_retries; int /*<<< orphan*/  num_of_bursts; int /*<<< orphan*/  samples_per_burst; int /*<<< orphan*/  burst_period; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ctrl_ch_position; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  channel_num; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {scalar_t__ request_civicloc; scalar_t__ request_lci; scalar_t__ asap; int /*<<< orphan*/  ftmr_retries; int /*<<< orphan*/  num_bursts_exp; int /*<<< orphan*/  ftms_per_burst; int /*<<< orphan*/  burst_period; } ;
struct cfg80211_pmsr_request_peer {TYPE_1__ ftm; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_FFT ; 
 int /*<<< orphan*/  ALGO_LR ; 
 int /*<<< orphan*/  ASAP ; 
 int /*<<< orphan*/  CIVIC_REQUEST ; 
 int /*<<< orphan*/  DYN_ACK ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FTM_PUT_FLAG (int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_MVM_FTM_INITIATOR_ALGO ; 
 scalar_t__ IWL_MVM_FTM_INITIATOR_DYNACK ; 
 scalar_t__ IWL_TOF_ALGO_TYPE_FFT ; 
 scalar_t__ IWL_TOF_ALGO_TYPE_LINEAR_REG ; 
 int /*<<< orphan*/  LCI_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_ftm_target_chandef (struct iwl_mvm*,struct cfg80211_pmsr_request_peer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_ftm_put_target(struct iwl_mvm *mvm,
				  struct cfg80211_pmsr_request_peer *peer,
				  struct iwl_tof_range_req_ap_entry *target)
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
	target->ftmr_max_retries = peer->ftm.ftmr_retries;
	target->initiator_ap_flags = cpu_to_le32(0);

	if (peer->ftm.asap)
		FTM_PUT_FLAG(ASAP);

	if (peer->ftm.request_lci)
		FTM_PUT_FLAG(LCI_REQUEST);

	if (peer->ftm.request_civicloc)
		FTM_PUT_FLAG(CIVIC_REQUEST);

	if (IWL_MVM_FTM_INITIATOR_DYNACK)
		FTM_PUT_FLAG(DYN_ACK);

	if (IWL_MVM_FTM_INITIATOR_ALGO == IWL_TOF_ALGO_TYPE_LINEAR_REG)
		FTM_PUT_FLAG(ALGO_LR);
	else if (IWL_MVM_FTM_INITIATOR_ALGO == IWL_TOF_ALGO_TYPE_FFT)
		FTM_PUT_FLAG(ALGO_FFT);

	return 0;
}