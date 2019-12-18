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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CCK_RATE_LEN ; 
 int /*<<< orphan*/  IEEE80211_NUM_OFDM_RATESLEN ; 
 int /*<<< orphan*/  NDIS_802_11_LENGTH_RATES_EX ; 
 int /*<<< orphan*/  WIFI_CCKRATES ; 
 int /*<<< orphan*/  WIFI_OFDMRATES ; 
#define  WIRELESS_11A 136 
#define  WIRELESS_11A_5N 135 
#define  WIRELESS_11B 134 
#define  WIRELESS_11BG 133 
#define  WIRELESS_11BG_24N 132 
#define  WIRELESS_11G 131 
#define  WIRELESS_11G_24N 130 
#define  WIRELESS_11_24N 129 
#define  WIRELESS_11_5N 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_set_supported_rate(u8 *SupportedRates, uint mode)
{
	memset(SupportedRates, 0, NDIS_802_11_LENGTH_RATES_EX);

	switch (mode) {
	case WIRELESS_11B:
		memcpy(SupportedRates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		break;
	case WIRELESS_11G:
	case WIRELESS_11A:
	case WIRELESS_11_5N:
	case WIRELESS_11A_5N:/* Todo: no basic rate for ofdm ? */
		memcpy(SupportedRates, WIFI_OFDMRATES, IEEE80211_NUM_OFDM_RATESLEN);
		break;
	case WIRELESS_11BG:
	case WIRELESS_11G_24N:
	case WIRELESS_11_24N:
	case WIRELESS_11BG_24N:
		memcpy(SupportedRates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		memcpy(SupportedRates + IEEE80211_CCK_RATE_LEN, WIFI_OFDMRATES, IEEE80211_NUM_OFDM_RATESLEN);
		break;
	}
}