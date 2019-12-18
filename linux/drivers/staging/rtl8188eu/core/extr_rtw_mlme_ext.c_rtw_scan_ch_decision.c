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
struct rtw_ieee80211_channel {int flags; scalar_t__ hw_value; } ;
struct mlme_ext_priv {int max_chan_nums; TYPE_1__* channel_set; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_2__ {scalar_t__ ScanType; scalar_t__ ChannelNum; } ;

/* Variables and functions */
 int RTW_IEEE80211_CHAN_DISABLED ; 
 int RTW_IEEE80211_CHAN_PASSIVE_SCAN ; 
 scalar_t__ SCAN_PASSIVE ; 
 int /*<<< orphan*/  memset (struct rtw_ieee80211_channel*,int /*<<< orphan*/ ,int) ; 
 int rtw_ch_set_search_ch (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int rtw_scan_ch_decision(struct adapter *padapter,
				struct rtw_ieee80211_channel *out,
				u32 out_num,
				struct rtw_ieee80211_channel *in, u32 in_num)
{
	int i, j;
	int set_idx;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	/* clear out first */
	memset(out, 0, sizeof(struct rtw_ieee80211_channel)*out_num);

	/* acquire channels from in */
	j = 0;
	for (i = 0; i < in_num; i++) {
		set_idx = rtw_ch_set_search_ch(pmlmeext->channel_set, in[i].hw_value);
		if (in[i].hw_value && !(in[i].flags & RTW_IEEE80211_CHAN_DISABLED) &&
		    set_idx >= 0) {
			out[j] = in[i];

			if (pmlmeext->channel_set[set_idx].ScanType == SCAN_PASSIVE)
				out[j].flags &= RTW_IEEE80211_CHAN_PASSIVE_SCAN;

			j++;
		}
		if (j >= out_num)
			break;
	}

	/* if out is empty, use channel_set as default */
	if (j == 0) {
		for (i = 0; i < pmlmeext->max_chan_nums; i++) {
			out[i].hw_value = pmlmeext->channel_set[i].ChannelNum;

			if (pmlmeext->channel_set[i].ScanType == SCAN_PASSIVE)
				out[i].flags &= RTW_IEEE80211_CHAN_PASSIVE_SCAN;

			j++;
		}
	}

	return j;
}