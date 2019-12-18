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
struct wcn36xx_hal_config_sta_params {void* dsss_cck_mode_40mhz; void* delayed_ba_support; void* green_field_capable; void* sgi_40mhz; void* sgi_20Mhz; void* max_amsdu_size; int /*<<< orphan*/  max_ampdu_density; int /*<<< orphan*/  max_ampdu_size; void* lsig_txop_protection; void* tx_channel_width_set; scalar_t__ ht_capable; } ;
struct TYPE_2__ {unsigned long cap; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; scalar_t__ ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HT_CAP_DELAY_BA ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_DSSSCCK40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_GRN_FLD ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_LSIG_TXOP_PROT ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_MAX_AMSDU ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 void* is_cap_supported (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcn36xx_smd_set_sta_ht_params(struct ieee80211_sta *sta,
		struct wcn36xx_hal_config_sta_params *sta_params)
{
	if (sta->ht_cap.ht_supported) {
		unsigned long caps = sta->ht_cap.cap;
		sta_params->ht_capable = sta->ht_cap.ht_supported;
		sta_params->tx_channel_width_set = is_cap_supported(caps,
			IEEE80211_HT_CAP_SUP_WIDTH_20_40);
		sta_params->lsig_txop_protection = is_cap_supported(caps,
			IEEE80211_HT_CAP_LSIG_TXOP_PROT);

		sta_params->max_ampdu_size = sta->ht_cap.ampdu_factor;
		sta_params->max_ampdu_density = sta->ht_cap.ampdu_density;
		sta_params->max_amsdu_size = is_cap_supported(caps,
			IEEE80211_HT_CAP_MAX_AMSDU);
		sta_params->sgi_20Mhz = is_cap_supported(caps,
			IEEE80211_HT_CAP_SGI_20);
		sta_params->sgi_40mhz =	is_cap_supported(caps,
			IEEE80211_HT_CAP_SGI_40);
		sta_params->green_field_capable = is_cap_supported(caps,
			IEEE80211_HT_CAP_GRN_FLD);
		sta_params->delayed_ba_support = is_cap_supported(caps,
			IEEE80211_HT_CAP_DELAY_BA);
		sta_params->dsss_cck_mode_40mhz = is_cap_supported(caps,
			IEEE80211_HT_CAP_DSSSCCK40);
	}
}