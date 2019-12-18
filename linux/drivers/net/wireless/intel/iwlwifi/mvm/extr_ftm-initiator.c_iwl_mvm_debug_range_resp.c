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
typedef  int u8 ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int rtt_avg; int burst_index; int num_ftmr_successes; int rssi_avg; int rssi_spread; int rtt_variance; int rtt_spread; } ;
struct cfg80211_pmsr_result {int status; int addr; int host_time; TYPE_1__ ftm; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int) ; 
 int div_s64 (int,int) ; 

__attribute__((used)) static void iwl_mvm_debug_range_resp(struct iwl_mvm *mvm, u8 index,
				     struct cfg80211_pmsr_result *res)
{
	s64 rtt_avg = div_s64(res->ftm.rtt_avg * 100, 6666);

	IWL_DEBUG_INFO(mvm, "entry %d\n", index);
	IWL_DEBUG_INFO(mvm, "\tstatus: %d\n", res->status);
	IWL_DEBUG_INFO(mvm, "\tBSSID: %pM\n", res->addr);
	IWL_DEBUG_INFO(mvm, "\thost time: %llu\n", res->host_time);
	IWL_DEBUG_INFO(mvm, "\tburst index: %hhu\n", res->ftm.burst_index);
	IWL_DEBUG_INFO(mvm, "\tsuccess num: %u\n", res->ftm.num_ftmr_successes);
	IWL_DEBUG_INFO(mvm, "\trssi: %d\n", res->ftm.rssi_avg);
	IWL_DEBUG_INFO(mvm, "\trssi spread: %hhu\n", res->ftm.rssi_spread);
	IWL_DEBUG_INFO(mvm, "\trtt: %lld\n", res->ftm.rtt_avg);
	IWL_DEBUG_INFO(mvm, "\trtt var: %llu\n", res->ftm.rtt_variance);
	IWL_DEBUG_INFO(mvm, "\trtt spread: %llu\n", res->ftm.rtt_spread);
	IWL_DEBUG_INFO(mvm, "\tdistance: %lld\n", rtt_avg);
}