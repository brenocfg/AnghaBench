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
typedef  int u32 ;
struct ieee80211_supported_band {scalar_t__ band; } ;
struct ieee80211_rate {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_2GHZ ; 
 int RTW_2G_CHANNELS_NUM ; 
 int RTW_G_RATES_NUM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtw_spt_band_free(struct ieee80211_supported_band *spt_band)
{
	u32 size = 0;

	if (!spt_band)
		return;

	if (spt_band->band == NL80211_BAND_2GHZ)
	{
		size = sizeof(struct ieee80211_supported_band)
			+ sizeof(struct ieee80211_channel)*RTW_2G_CHANNELS_NUM
			+ sizeof(struct ieee80211_rate)*RTW_G_RATES_NUM;
	}
	kfree((u8 *)spt_band);
}