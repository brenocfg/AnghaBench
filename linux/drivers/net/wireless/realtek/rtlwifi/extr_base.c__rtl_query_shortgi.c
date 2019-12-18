#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_tcb_desc {int use_shortgi; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; int bw_80; } ;
struct TYPE_6__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct TYPE_8__ {int cap; int vht_supported; } ;
struct TYPE_7__ {int cap; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {TYPE_4__ vht_cap; TYPE_3__ ht_cap; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_VHT_CAP_SHORT_GI_80 ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 struct rtl_mac* rtl_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_query_shortgi(struct ieee80211_hw *hw,
			       struct ieee80211_sta *sta,
			       struct rtl_tcb_desc *tcb_desc,
			       struct ieee80211_tx_info *info)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 rate_flag = info->control.rates[0].flags;
	u8 sgi_40 = 0, sgi_20 = 0, bw_40 = 0;
	u8 sgi_80 = 0, bw_80 = 0;

	tcb_desc->use_shortgi = false;

	if (sta == NULL)
		return;

	sgi_40 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40;
	sgi_20 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20;
	sgi_80 = sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80;

	if ((!sta->ht_cap.ht_supported) && (!sta->vht_cap.vht_supported))
		return;

	if (!sgi_40 && !sgi_20)
		return;

	if (mac->opmode == NL80211_IFTYPE_STATION) {
		bw_40 = mac->bw_40;
		bw_80 = mac->bw_80;
	} else if (mac->opmode == NL80211_IFTYPE_AP ||
		 mac->opmode == NL80211_IFTYPE_ADHOC ||
		 mac->opmode == NL80211_IFTYPE_MESH_POINT) {
		bw_40 = sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		bw_80 = sta->vht_cap.vht_supported;
	}

	if (bw_80) {
		if (sgi_80)
			tcb_desc->use_shortgi = true;
		else
			tcb_desc->use_shortgi = false;
	} else {
		if (bw_40 && sgi_40)
			tcb_desc->use_shortgi = true;
		else if (!bw_40 && sgi_20)
			tcb_desc->use_shortgi = true;
	}

	if (!(rate_flag & IEEE80211_TX_RC_SHORT_GI))
		tcb_desc->use_shortgi = false;
}