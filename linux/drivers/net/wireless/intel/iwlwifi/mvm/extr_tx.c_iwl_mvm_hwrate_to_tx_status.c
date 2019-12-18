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
typedef  int u32 ;
struct ieee80211_tx_rate {int dummy; } ;
struct TYPE_2__ {int antenna; struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  band; TYPE_1__ status; } ;

/* Variables and functions */
 int RATE_MCS_ANT_ABC_MSK ; 
 int RATE_MCS_ANT_POS ; 
 int /*<<< orphan*/  iwl_mvm_hwrate_to_tx_rate (int,int /*<<< orphan*/ ,struct ieee80211_tx_rate*) ; 

__attribute__((used)) static void iwl_mvm_hwrate_to_tx_status(u32 rate_n_flags,
					struct ieee80211_tx_info *info)
{
	struct ieee80211_tx_rate *r = &info->status.rates[0];

	info->status.antenna =
		((rate_n_flags & RATE_MCS_ANT_ABC_MSK) >> RATE_MCS_ANT_POS);
	iwl_mvm_hwrate_to_tx_rate(rate_n_flags, info->band, r);
}