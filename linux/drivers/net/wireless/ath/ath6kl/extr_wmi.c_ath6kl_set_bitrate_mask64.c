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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct wmi_set_tx_select_rates64_cmd {int /*<<< orphan*/ * ratemask; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct cfg80211_bitrate_mask {TYPE_1__* control; } ;
typedef  int /*<<< orphan*/  ratemask ;
struct TYPE_2__ {int legacy; int* ht_mcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ATH6KL_NUM_BANDS ; 
 int ENOMEM ; 
 int NL80211_BAND_2GHZ ; 
 int NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int WMI_RATES_MODE_11A ; 
 int WMI_RATES_MODE_11A_HT20 ; 
 int WMI_RATES_MODE_11A_HT40 ; 
 int WMI_RATES_MODE_MAX ; 
 int /*<<< orphan*/  WMI_SET_TX_SELECT_RATES_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath6kl_set_bitrate_mask64(struct wmi *wmi, u8 if_idx,
				     const struct cfg80211_bitrate_mask *mask)
{
	struct sk_buff *skb;
	int ret, mode, band;
	u64 mcsrate, ratemask[ATH6KL_NUM_BANDS];
	struct wmi_set_tx_select_rates64_cmd *cmd;

	memset(&ratemask, 0, sizeof(ratemask));

	/* only check 2.4 and 5 GHz bands, skip the rest */
	for (band = 0; band <= NL80211_BAND_5GHZ; band++) {
		/* copy legacy rate mask */
		ratemask[band] = mask->control[band].legacy;
		if (band == NL80211_BAND_5GHZ)
			ratemask[band] =
				mask->control[band].legacy << 4;

		/* copy mcs rate mask */
		mcsrate = mask->control[band].ht_mcs[1];
		mcsrate <<= 8;
		mcsrate |= mask->control[band].ht_mcs[0];
		ratemask[band] |= mcsrate << 12;
		ratemask[band] |= mcsrate << 28;
	}

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "Ratemask 64 bit: 2.4:%llx 5:%llx\n",
		   ratemask[0], ratemask[1]);

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd) * WMI_RATES_MODE_MAX);
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_set_tx_select_rates64_cmd *) skb->data;
	for (mode = 0; mode < WMI_RATES_MODE_MAX; mode++) {
		/* A mode operate in 5GHZ band */
		if (mode == WMI_RATES_MODE_11A ||
		    mode == WMI_RATES_MODE_11A_HT20 ||
		    mode == WMI_RATES_MODE_11A_HT40)
			band = NL80211_BAND_5GHZ;
		else
			band = NL80211_BAND_2GHZ;
		cmd->ratemask[mode] = cpu_to_le64(ratemask[band]);
	}

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb,
				  WMI_SET_TX_SELECT_RATES_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}