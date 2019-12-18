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
struct ieee80211_supported_band {int band; int n_channels; int n_bitrates; struct ieee80211_rate* bitrates; struct ieee80211_channel* channels; } ;
struct ieee80211_rate {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int NL80211_BAND_2GHZ ; 
 int RTW_2G_CHANNELS_NUM ; 
 int RTW_G_RATES_NUM ; 
 int /*<<< orphan*/  rtw_2g_channels_init (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  rtw_2g_rates_init (struct ieee80211_rate*) ; 
 struct ieee80211_supported_band* rtw_zmalloc (int) ; 

__attribute__((used)) static struct ieee80211_supported_band *rtw_spt_band_alloc(
	enum nl80211_band band
	)
{
	struct ieee80211_supported_band *spt_band = NULL;
	int n_channels, n_bitrates;

	if (band == NL80211_BAND_2GHZ)
	{
		n_channels = RTW_2G_CHANNELS_NUM;
		n_bitrates = RTW_G_RATES_NUM;
	}
	else
	{
		goto exit;
	}

	spt_band = rtw_zmalloc(sizeof(struct ieee80211_supported_band) +
			       sizeof(struct ieee80211_channel) * n_channels +
			       sizeof(struct ieee80211_rate) * n_bitrates);
	if (!spt_band)
		goto exit;

	spt_band->channels = (struct ieee80211_channel*)(((u8 *)spt_band)+sizeof(struct ieee80211_supported_band));
	spt_band->bitrates = (struct ieee80211_rate*)(((u8 *)spt_band->channels)+sizeof(struct ieee80211_channel)*n_channels);
	spt_band->band = band;
	spt_band->n_channels = n_channels;
	spt_band->n_bitrates = n_bitrates;

	if (band == NL80211_BAND_2GHZ)
	{
		rtw_2g_channels_init(spt_band->channels);
		rtw_2g_rates_init(spt_band->bitrates);
	}

	/* spt_band.ht_cap */

exit:

	return spt_band;
}