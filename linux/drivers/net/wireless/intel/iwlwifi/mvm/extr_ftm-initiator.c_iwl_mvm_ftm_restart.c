#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* req; int /*<<< orphan*/  req_wdev; int /*<<< orphan*/ * responses; } ;
struct iwl_mvm {TYPE_3__ ftm_initiator; int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  burst_index; } ;
struct cfg80211_pmsr_result {int final; TYPE_2__ ftm; int /*<<< orphan*/  addr; int /*<<< orphan*/  type; int /*<<< orphan*/  host_time; int /*<<< orphan*/  status; } ;
struct TYPE_9__ {int n_peers; TYPE_1__* peers; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_PMSR_STATUS_FAILURE ; 
 int /*<<< orphan*/  NL80211_PMSR_TYPE_FTM ; 
 int /*<<< orphan*/  cfg80211_pmsr_complete (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_pmsr_report (int /*<<< orphan*/ ,TYPE_4__*,struct cfg80211_pmsr_result*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_ftm_reset (struct iwl_mvm*) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_mvm_ftm_restart(struct iwl_mvm *mvm)
{
	struct cfg80211_pmsr_result result = {
		.status = NL80211_PMSR_STATUS_FAILURE,
		.final = 1,
		.host_time = ktime_get_boottime_ns(),
		.type = NL80211_PMSR_TYPE_FTM,
	};
	int i;

	lockdep_assert_held(&mvm->mutex);

	if (!mvm->ftm_initiator.req)
		return;

	for (i = 0; i < mvm->ftm_initiator.req->n_peers; i++) {
		memcpy(result.addr, mvm->ftm_initiator.req->peers[i].addr,
		       ETH_ALEN);
		result.ftm.burst_index = mvm->ftm_initiator.responses[i];

		cfg80211_pmsr_report(mvm->ftm_initiator.req_wdev,
				     mvm->ftm_initiator.req,
				     &result, GFP_KERNEL);
	}

	cfg80211_pmsr_complete(mvm->ftm_initiator.req_wdev,
			       mvm->ftm_initiator.req, GFP_KERNEL);
	iwl_mvm_ftm_reset(mvm);
}