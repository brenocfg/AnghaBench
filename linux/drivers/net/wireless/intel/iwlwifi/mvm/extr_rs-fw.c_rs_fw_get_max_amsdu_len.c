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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sta_vht_cap {int cap; scalar_t__ vht_supported; } ;
struct ieee80211_sta_ht_cap {int cap; scalar_t__ ht_supported; } ;
struct ieee80211_sta {struct ieee80211_sta_ht_cap ht_cap; struct ieee80211_sta_vht_cap vht_cap; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_MAX_AMSDU ; 
 int /*<<< orphan*/  IEEE80211_MAX_MPDU_LEN_HT_3839 ; 
 int /*<<< orphan*/  IEEE80211_MAX_MPDU_LEN_HT_BA ; 
 int /*<<< orphan*/  IEEE80211_MAX_MPDU_LEN_VHT_11454 ; 
 int /*<<< orphan*/  IEEE80211_MAX_MPDU_LEN_VHT_3895 ; 
 int /*<<< orphan*/  IEEE80211_MAX_MPDU_LEN_VHT_7991 ; 
#define  IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 129 
#define  IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991 128 
 int IEEE80211_VHT_CAP_MAX_MPDU_MASK ; 

__attribute__((used)) static u16 rs_fw_get_max_amsdu_len(struct ieee80211_sta *sta)
{
	const struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	const struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;

	if (vht_cap->vht_supported) {
		switch (vht_cap->cap & IEEE80211_VHT_CAP_MAX_MPDU_MASK) {
		case IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454:
			return IEEE80211_MAX_MPDU_LEN_VHT_11454;
		case IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991:
			return IEEE80211_MAX_MPDU_LEN_VHT_7991;
		default:
			return IEEE80211_MAX_MPDU_LEN_VHT_3895;
	}

	} else if (ht_cap->ht_supported) {
		if (ht_cap->cap & IEEE80211_HT_CAP_MAX_AMSDU)
			/*
			 * agg is offloaded so we need to assume that agg
			 * are enabled and max mpdu in ampdu is 4095
			 * (spec 802.11-2016 9.3.2.1)
			 */
			return IEEE80211_MAX_MPDU_LEN_HT_BA;
		else
			return IEEE80211_MAX_MPDU_LEN_HT_3839;
	}

	/* in legacy mode no amsdu is enabled so return zero */
	return 0;
}