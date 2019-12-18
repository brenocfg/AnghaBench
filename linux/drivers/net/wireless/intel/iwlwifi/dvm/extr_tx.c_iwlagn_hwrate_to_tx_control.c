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
struct iwl_priv {int dummy; } ;
struct ieee80211_tx_rate {int /*<<< orphan*/  idx; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int antenna; struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  band; TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_DUP_DATA ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_GREEN_FIELD ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 int RATE_MCS_ANT_ABC_MSK ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_DUP_MSK ; 
 int RATE_MCS_GF_MSK ; 
 int RATE_MCS_HT40_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 int /*<<< orphan*/  iwlagn_hwrate_to_mac80211_idx (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwlagn_hwrate_to_tx_control(struct iwl_priv *priv, u32 rate_n_flags,
				  struct ieee80211_tx_info *info)
{
	struct ieee80211_tx_rate *r = &info->status.rates[0];

	info->status.antenna =
		((rate_n_flags & RATE_MCS_ANT_ABC_MSK) >> RATE_MCS_ANT_POS);
	if (rate_n_flags & RATE_MCS_HT_MSK)
		r->flags |= IEEE80211_TX_RC_MCS;
	if (rate_n_flags & RATE_MCS_GF_MSK)
		r->flags |= IEEE80211_TX_RC_GREEN_FIELD;
	if (rate_n_flags & RATE_MCS_HT40_MSK)
		r->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
	if (rate_n_flags & RATE_MCS_DUP_MSK)
		r->flags |= IEEE80211_TX_RC_DUP_DATA;
	if (rate_n_flags & RATE_MCS_SGI_MSK)
		r->flags |= IEEE80211_TX_RC_SHORT_GI;
	r->idx = iwlagn_hwrate_to_mac80211_idx(rate_n_flags, info->band);
}