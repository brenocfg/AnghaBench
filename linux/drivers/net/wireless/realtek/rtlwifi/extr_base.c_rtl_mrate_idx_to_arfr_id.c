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
struct rtl_phy {int /*<<< orphan*/  rf_type; int /*<<< orphan*/  current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_80 ; 
 int RATEID_IDX_B ; 
 int RATEID_IDX_BG ; 
 int RATEID_IDX_BGN_20M_1SS_BN ; 
 int RATEID_IDX_BGN_20M_2SS_BN ; 
 int RATEID_IDX_BGN_40M_1SS ; 
 int RATEID_IDX_BGN_40M_2SS ; 
 int RATEID_IDX_G ; 
 int RATEID_IDX_GN_N1SS ; 
 int RATEID_IDX_GN_N2SS ; 
 int RATEID_IDX_MIX1 ; 
 int RATEID_IDX_MIX2 ; 
 int RATEID_IDX_VHT_1SS ; 
 int RATEID_IDX_VHT_2SS ; 
#define  RATR_INX_WIRELESS_AC_24N 137 
#define  RATR_INX_WIRELESS_AC_5N 136 
#define  RATR_INX_WIRELESS_B 135 
#define  RATR_INX_WIRELESS_G 134 
#define  RATR_INX_WIRELESS_GB 133 
#define  RATR_INX_WIRELESS_MC 132 
#define  RATR_INX_WIRELESS_N 131 
#define  RATR_INX_WIRELESS_NB 130 
#define  RATR_INX_WIRELESS_NG 129 
#define  RATR_INX_WIRELESS_NGB 128 
 int /*<<< orphan*/  RF_1T1R ; 
 int WIRELESS_MODE_AC_24G ; 
 int WIRELESS_MODE_B ; 
 int WIRELESS_MODE_G ; 
 int WIRELESS_MODE_N_24G ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u8 rtl_mrate_idx_to_arfr_id(struct ieee80211_hw *hw, u8 rate_index,
			    enum wireless_mode wirelessmode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 ret = 0;

	switch (rate_index) {
	case RATR_INX_WIRELESS_NGB:
		if (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_BGN_40M_1SS;
		else
			ret = RATEID_IDX_BGN_40M_2SS;
		; break;
	case RATR_INX_WIRELESS_N:
	case RATR_INX_WIRELESS_NG:
		if (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_GN_N1SS;
		else
			ret = RATEID_IDX_GN_N2SS;
		; break;
	case RATR_INX_WIRELESS_NB:
		if (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_BGN_20M_1SS_BN;
		else
			ret = RATEID_IDX_BGN_20M_2SS_BN;
		; break;
	case RATR_INX_WIRELESS_GB:
		ret = RATEID_IDX_BG;
		break;
	case RATR_INX_WIRELESS_G:
		ret = RATEID_IDX_G;
		break;
	case RATR_INX_WIRELESS_B:
		ret = RATEID_IDX_B;
		break;
	case RATR_INX_WIRELESS_MC:
		if (wirelessmode == WIRELESS_MODE_B ||
		    wirelessmode == WIRELESS_MODE_G ||
		    wirelessmode == WIRELESS_MODE_N_24G ||
		    wirelessmode == WIRELESS_MODE_AC_24G)
			ret = RATEID_IDX_BG;
		else
			ret = RATEID_IDX_G;
		break;
	case RATR_INX_WIRELESS_AC_5N:
		if (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_VHT_1SS;
		else
			ret = RATEID_IDX_VHT_2SS;
		break;
	case RATR_INX_WIRELESS_AC_24N:
		if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) {
			if (rtlphy->rf_type == RF_1T1R)
				ret = RATEID_IDX_VHT_1SS;
			else
				ret = RATEID_IDX_VHT_2SS;
		} else {
			if (rtlphy->rf_type == RF_1T1R)
				ret = RATEID_IDX_MIX1;
			else
				ret = RATEID_IDX_MIX2;
		}
		break;
	default:
		ret = RATEID_IDX_BGN_40M_2SS;
		break;
	}
	return ret;
}