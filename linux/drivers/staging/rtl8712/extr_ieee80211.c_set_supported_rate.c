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
#define  WIRELESS_11A 131 
#define  WIRELESS_11B 130 
#define  WIRELESS_11BG 129 
#define  WIRELESS_11G 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_supported_rate(u8 *rates, uint mode)
{
	memset(rates, 0, NDIS_802_11_LENGTH_RATES_EX);
	switch (mode) {
	case WIRELESS_11B:
		memcpy(rates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		break;
	case WIRELESS_11G:
	case WIRELESS_11A:
		memcpy(rates, WIFI_OFDMRATES, IEEE80211_NUM_OFDM_RATESLEN);
		break;
	case WIRELESS_11BG:
		memcpy(rates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		memcpy(rates + IEEE80211_CCK_RATE_LEN, WIFI_OFDMRATES,
		       IEEE80211_NUM_OFDM_RATESLEN);
		break;
	}
}