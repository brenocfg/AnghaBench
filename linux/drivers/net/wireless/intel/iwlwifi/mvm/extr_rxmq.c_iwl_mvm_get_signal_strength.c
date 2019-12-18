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
typedef  int u32 ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_rx_status {int signal; int chains; int* chain_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_STATS (struct iwl_mvm*,char*,int,int,int) ; 
 int RATE_MCS_ANT_AB_MSK ; 
 int RATE_MCS_ANT_POS ; 
 int S8_MIN ; 
 int max (int,int) ; 

__attribute__((used)) static void iwl_mvm_get_signal_strength(struct iwl_mvm *mvm,
					struct ieee80211_rx_status *rx_status,
					u32 rate_n_flags, int energy_a,
					int energy_b)
{
	int max_energy;
	u32 rate_flags = rate_n_flags;

	energy_a = energy_a ? -energy_a : S8_MIN;
	energy_b = energy_b ? -energy_b : S8_MIN;
	max_energy = max(energy_a, energy_b);

	IWL_DEBUG_STATS(mvm, "energy In A %d B %d, and max %d\n",
			energy_a, energy_b, max_energy);

	rx_status->signal = max_energy;
	rx_status->chains =
		(rate_flags & RATE_MCS_ANT_AB_MSK) >> RATE_MCS_ANT_POS;
	rx_status->chain_signal[0] = energy_a;
	rx_status->chain_signal[1] = energy_b;
	rx_status->chain_signal[2] = S8_MIN;
}