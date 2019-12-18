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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_phy {int current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_WIFI_BW_HT20 ; 
 int /*<<< orphan*/  BTC_WIFI_BW_HT40 ; 
 int /*<<< orphan*/  BTC_WIFI_BW_HT80 ; 
 int /*<<< orphan*/  BTC_WIFI_BW_LEGACY ; 
#define  HT_CHANNEL_WIDTH_20 130 
#define  HT_CHANNEL_WIDTH_20_40 129 
#define  HT_CHANNEL_WIDTH_80 128 
 scalar_t__ halbtc_legacy (struct rtl_priv*) ; 

__attribute__((used)) static u32 halbtc_get_wifi_bw(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u32 wifi_bw = BTC_WIFI_BW_HT20;

	if (halbtc_legacy(rtlpriv)) {
		wifi_bw = BTC_WIFI_BW_LEGACY;
	} else {
		switch (rtlphy->current_chan_bw) {
		case HT_CHANNEL_WIDTH_20:
			wifi_bw = BTC_WIFI_BW_HT20;
			break;
		case HT_CHANNEL_WIDTH_20_40:
			wifi_bw = BTC_WIFI_BW_HT40;
			break;
		case HT_CHANNEL_WIDTH_80:
			wifi_bw = BTC_WIFI_BW_HT80;
			break;
		}
	}

	return wifi_bw;
}