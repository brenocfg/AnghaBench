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
typedef  size_t u8 ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_hal rtlhal; struct rtl_phy phy; } ;
struct rtl_efuse {size_t** txpwrlevel_cck; size_t** txpwrlevel_ht40_1s; size_t** txpwrlevel_ht40_2s; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T2R ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92d_get_txpower_index(struct ieee80211_hw *hw, u8 channel,
	u8 *cckpowerlevel, u8 *ofdmpowerlevel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);

	/* 1. CCK */
	if (rtlhal->current_bandtype == BAND_ON_2_4G) {
		/* RF-A */
		cckpowerlevel[RF90_PATH_A] =
				 rtlefuse->txpwrlevel_cck[RF90_PATH_A][index];
		/* RF-B */
		cckpowerlevel[RF90_PATH_B] =
				 rtlefuse->txpwrlevel_cck[RF90_PATH_B][index];
	} else {
		cckpowerlevel[RF90_PATH_A] = 0;
		cckpowerlevel[RF90_PATH_B] = 0;
	}
	/* 2. OFDM for 1S or 2S */
	if (rtlphy->rf_type == RF_1T2R || rtlphy->rf_type == RF_1T1R) {
		/*  Read HT 40 OFDM TX power */
		ofdmpowerlevel[RF90_PATH_A] =
		    rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index];
		ofdmpowerlevel[RF90_PATH_B] =
		    rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index];
	} else if (rtlphy->rf_type == RF_2T2R) {
		/* Read HT 40 OFDM TX power */
		ofdmpowerlevel[RF90_PATH_A] =
		    rtlefuse->txpwrlevel_ht40_2s[RF90_PATH_A][index];
		ofdmpowerlevel[RF90_PATH_B] =
		    rtlefuse->txpwrlevel_ht40_2s[RF90_PATH_B][index];
	}
}