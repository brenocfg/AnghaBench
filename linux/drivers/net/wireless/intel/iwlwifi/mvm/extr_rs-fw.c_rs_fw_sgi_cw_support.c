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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_sta_vht_cap {int cap; } ;
struct ieee80211_sta_ht_cap {int cap; } ;
struct ieee80211_sta_he_cap {scalar_t__ has_he; } ;
struct ieee80211_sta {struct ieee80211_sta_he_cap he_cap; struct ieee80211_sta_vht_cap vht_cap; struct ieee80211_sta_ht_cap ht_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_VHT_CAP_SHORT_GI_160 ; 
 int IEEE80211_VHT_CAP_SHORT_GI_80 ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CH_WIDTH_160MHZ ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CH_WIDTH_20MHZ ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CH_WIDTH_40MHZ ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CH_WIDTH_80MHZ ; 

__attribute__((used)) static u8 rs_fw_sgi_cw_support(struct ieee80211_sta *sta)
{
	struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	struct ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	u8 supp = 0;

	if (he_cap->has_he)
		return 0;

	if (ht_cap->cap & IEEE80211_HT_CAP_SGI_20)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_20MHZ);
	if (ht_cap->cap & IEEE80211_HT_CAP_SGI_40)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_40MHZ);
	if (vht_cap->cap & IEEE80211_VHT_CAP_SHORT_GI_80)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_80MHZ);
	if (vht_cap->cap & IEEE80211_VHT_CAP_SHORT_GI_160)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_160MHZ);

	return supp;
}