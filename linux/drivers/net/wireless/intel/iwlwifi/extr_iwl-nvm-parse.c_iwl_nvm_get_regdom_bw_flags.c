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
typedef  scalar_t__ u16 ;
struct iwl_cfg {int dummy; } ;

/* Variables and functions */
 scalar_t__ const FIRST_2GHZ_HT_MINUS ; 
 scalar_t__ const LAST_2GHZ_HT_PLUS ; 
 int NL80211_RRF_DFS ; 
 int NL80211_RRF_GO_CONCURRENT ; 
 int NL80211_RRF_NO_160MHZ ; 
 int NL80211_RRF_NO_80MHZ ; 
 int NL80211_RRF_NO_HT40 ; 
 int NL80211_RRF_NO_HT40MINUS ; 
 int NL80211_RRF_NO_HT40PLUS ; 
 int NL80211_RRF_NO_IR ; 
 int NL80211_RRF_NO_OUTDOOR ; 
 int NUM_2GHZ_CHANNELS ; 
 scalar_t__ NVM_CHANNEL_160MHZ ; 
 scalar_t__ NVM_CHANNEL_40MHZ ; 
 scalar_t__ NVM_CHANNEL_80MHZ ; 
 scalar_t__ NVM_CHANNEL_ACTIVE ; 
 scalar_t__ NVM_CHANNEL_GO_CONCURRENT ; 
 scalar_t__ NVM_CHANNEL_INDOOR_ONLY ; 
 scalar_t__ NVM_CHANNEL_RADAR ; 

__attribute__((used)) static u32 iwl_nvm_get_regdom_bw_flags(const u16 *nvm_chan,
				       int ch_idx, u16 nvm_flags,
				       const struct iwl_cfg *cfg)
{
	u32 flags = NL80211_RRF_NO_HT40;

	if (ch_idx < NUM_2GHZ_CHANNELS &&
	    (nvm_flags & NVM_CHANNEL_40MHZ)) {
		if (nvm_chan[ch_idx] <= LAST_2GHZ_HT_PLUS)
			flags &= ~NL80211_RRF_NO_HT40PLUS;
		if (nvm_chan[ch_idx] >= FIRST_2GHZ_HT_MINUS)
			flags &= ~NL80211_RRF_NO_HT40MINUS;
	} else if (nvm_flags & NVM_CHANNEL_40MHZ) {
		if ((ch_idx - NUM_2GHZ_CHANNELS) % 2 == 0)
			flags &= ~NL80211_RRF_NO_HT40PLUS;
		else
			flags &= ~NL80211_RRF_NO_HT40MINUS;
	}

	if (!(nvm_flags & NVM_CHANNEL_80MHZ))
		flags |= NL80211_RRF_NO_80MHZ;
	if (!(nvm_flags & NVM_CHANNEL_160MHZ))
		flags |= NL80211_RRF_NO_160MHZ;

	if (!(nvm_flags & NVM_CHANNEL_ACTIVE))
		flags |= NL80211_RRF_NO_IR;

	if (nvm_flags & NVM_CHANNEL_RADAR)
		flags |= NL80211_RRF_DFS;

	if (nvm_flags & NVM_CHANNEL_INDOOR_ONLY)
		flags |= NL80211_RRF_NO_OUTDOOR;

	/* Set the GO concurrent flag only in case that NO_IR is set.
	 * Otherwise it is meaningless
	 */
	if ((nvm_flags & NVM_CHANNEL_GO_CONCURRENT) &&
	    (flags & NL80211_RRF_NO_IR))
		flags |= NL80211_RRF_GO_CONCURRENT;

	return flags;
}