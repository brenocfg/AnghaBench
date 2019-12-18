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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
#define  BAND_ON_2_4G 129 
#define  BAND_ON_5G 128 
 int BTC_NOT_SWITCH ; 
 int BTC_SWITCH_TO_24G ; 
 int BTC_SWITCH_TO_24G_NOFORSCAN ; 
 int BTC_SWITCH_TO_5G ; 
 int /*<<< orphan*/  exhalbtc_switch_band_notify (struct btc_coexist*,int) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

void rtl_btc_switch_band_notify(struct rtl_priv *rtlpriv, u8 band_type,
				bool scanning)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 type = BTC_NOT_SWITCH;

	if (!btcoexist)
		return;

	switch (band_type) {
	case BAND_ON_2_4G:
		if (scanning)
			type = BTC_SWITCH_TO_24G;
		else
			type = BTC_SWITCH_TO_24G_NOFORSCAN;
		break;

	case BAND_ON_5G:
		type = BTC_SWITCH_TO_5G;
		break;
	}

	if (type != BTC_NOT_SWITCH)
		exhalbtc_switch_band_notify(btcoexist, type);
}