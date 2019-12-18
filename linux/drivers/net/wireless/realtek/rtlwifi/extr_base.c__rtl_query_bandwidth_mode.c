#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtl_tcb_desc {int packet_bw; scalar_t__ hw_rate; scalar_t__ broadcast; scalar_t__ multicast; } ;
struct rtl_priv {TYPE_3__* cfg; } ;
struct rtl_mac {scalar_t__ opmode; int /*<<< orphan*/  bw_80; int /*<<< orphan*/  bw_40; } ;
struct TYPE_5__ {int /*<<< orphan*/  vht_supported; } ;
struct TYPE_4__ {int cap; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {TYPE_2__ vht_cap; TYPE_1__ ht_cap; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {scalar_t__* maps; int spec_ver; } ;

/* Variables and functions */
 int HT_CHANNEL_WIDTH_20_40 ; 
 int HT_CHANNEL_WIDTH_80 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 size_t RTL_RC_HT_RATEMCS15 ; 
 size_t RTL_RC_OFDM_RATE54M ; 
 int RTL_SPEC_SUPPORT_VHT ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_query_bandwidth_mode(struct ieee80211_hw *hw,
				      struct ieee80211_sta *sta,
				      struct rtl_tcb_desc *tcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	tcb_desc->packet_bw = false;
	if (!sta)
		return;
	if (mac->opmode == NL80211_IFTYPE_AP ||
	    mac->opmode == NL80211_IFTYPE_ADHOC ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT) {
		if (!(sta->ht_cap.ht_supported) ||
		    !(sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40))
			return;
	} else if (mac->opmode == NL80211_IFTYPE_STATION) {
		if (!mac->bw_40 || !(sta->ht_cap.ht_supported))
			return;
	}
	if (tcb_desc->multicast || tcb_desc->broadcast)
		return;

	/*use legency rate, shall use 20MHz */
	if (tcb_desc->hw_rate <= rtlpriv->cfg->maps[RTL_RC_OFDM_RATE54M])
		return;

	tcb_desc->packet_bw = HT_CHANNEL_WIDTH_20_40;

	if (rtlpriv->cfg->spec_ver & RTL_SPEC_SUPPORT_VHT) {
		if (mac->opmode == NL80211_IFTYPE_AP ||
		    mac->opmode == NL80211_IFTYPE_ADHOC ||
		    mac->opmode == NL80211_IFTYPE_MESH_POINT) {
			if (!(sta->vht_cap.vht_supported))
				return;
		} else if (mac->opmode == NL80211_IFTYPE_STATION) {
			if (!mac->bw_80 ||
			    !(sta->vht_cap.vht_supported))
				return;
		}
		if (tcb_desc->hw_rate <=
			rtlpriv->cfg->maps[RTL_RC_HT_RATEMCS15])
			return;
		tcb_desc->packet_bw = HT_CHANNEL_WIDTH_80;
	}
}