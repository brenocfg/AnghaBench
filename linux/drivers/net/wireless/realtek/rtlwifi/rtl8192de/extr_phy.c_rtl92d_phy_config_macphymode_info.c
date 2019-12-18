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
struct rtl_phy {void* rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {int macphymode; void* current_bandtype; void* bandset; int /*<<< orphan*/  interfaceindex; int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 void* BAND_ON_2_4G ; 
 void* BAND_ON_5G ; 
 void* BAND_ON_BOTH ; 
#define  DUALMAC_DUALPHY 130 
#define  DUALMAC_SINGLEPHY 129 
 void* RF_1T1R ; 
 void* RF_2T2R ; 
 int /*<<< orphan*/  RF_TYPE_1T1R ; 
 int /*<<< orphan*/  RF_TYPE_2T2R ; 
#define  SINGLEMAC_SINGLEPHY 128 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92d_phy_config_macphymode_info(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);

	switch (rtlhal->macphymode) {
	case DUALMAC_SINGLEPHY:
		rtlphy->rf_type = RF_2T2R;
		rtlhal->version |= RF_TYPE_2T2R;
		rtlhal->bandset = BAND_ON_BOTH;
		rtlhal->current_bandtype = BAND_ON_2_4G;
		break;

	case SINGLEMAC_SINGLEPHY:
		rtlphy->rf_type = RF_2T2R;
		rtlhal->version |= RF_TYPE_2T2R;
		rtlhal->bandset = BAND_ON_BOTH;
		rtlhal->current_bandtype = BAND_ON_2_4G;
		break;

	case DUALMAC_DUALPHY:
		rtlphy->rf_type = RF_1T1R;
		rtlhal->version &= RF_TYPE_1T1R;
		/* Now we let MAC0 run on 5G band. */
		if (rtlhal->interfaceindex == 0) {
			rtlhal->bandset = BAND_ON_5G;
			rtlhal->current_bandtype = BAND_ON_5G;
		} else {
			rtlhal->bandset = BAND_ON_2_4G;
			rtlhal->current_bandtype = BAND_ON_2_4G;
		}
		break;
	default:
		break;
	}
}