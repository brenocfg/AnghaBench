#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct TYPE_4__ {int width; TYPE_1__* chan; } ;
struct cfg80211_pmsr_request_peer {TYPE_2__ chandef; } ;
struct TYPE_3__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_TOF_BW_20_HT ; 
 int /*<<< orphan*/  IWL_TOF_BW_20_LEGACY ; 
 int /*<<< orphan*/  IWL_TOF_BW_40 ; 
 int /*<<< orphan*/  IWL_TOF_BW_80 ; 
#define  NL80211_CHAN_WIDTH_20 131 
#define  NL80211_CHAN_WIDTH_20_NOHT 130 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_get_ctrl_pos (TYPE_2__*) ; 

__attribute__((used)) static int iwl_mvm_ftm_target_chandef(struct iwl_mvm *mvm,
				      struct cfg80211_pmsr_request_peer *peer,
				      u8 *channel, u8 *bandwidth,
				      u8 *ctrl_ch_position)
{
	u32 freq = peer->chandef.chan->center_freq;

	*channel = ieee80211_frequency_to_channel(freq);

	switch (peer->chandef.width) {
	case NL80211_CHAN_WIDTH_20_NOHT:
		*bandwidth = IWL_TOF_BW_20_LEGACY;
		break;
	case NL80211_CHAN_WIDTH_20:
		*bandwidth = IWL_TOF_BW_20_HT;
		break;
	case NL80211_CHAN_WIDTH_40:
		*bandwidth = IWL_TOF_BW_40;
		break;
	case NL80211_CHAN_WIDTH_80:
		*bandwidth = IWL_TOF_BW_80;
		break;
	default:
		IWL_ERR(mvm, "Unsupported BW in FTM request (%d)\n",
			peer->chandef.width);
		return -EINVAL;
	}

	*ctrl_ch_position = (peer->chandef.width > NL80211_CHAN_WIDTH_20) ?
		iwl_mvm_get_ctrl_pos(&peer->chandef) : 0;

	return 0;
}