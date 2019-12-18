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
struct rtl_phy {void****** txpwr_limit_5g; void****** txpwr_limit_2_4g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t CHANNEL_MAX_NUMBER_2G ; 
 size_t CHANNEL_MAX_NUMBER_5G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 size_t MAX_2_4G_BANDWIDTH_NUM ; 
 size_t MAX_5G_BANDWIDTH_NUM ; 
 void* MAX_POWER_INDEX ; 
 size_t MAX_RATE_SECTION_NUM ; 
 size_t MAX_REGULATION_NUM ; 
 size_t MAX_RF_PATH_NUM ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8821ae_phy_init_txpower_limit(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 i, j, k, l, m;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "=====> _rtl8821ae_phy_init_txpower_limit()!\n");

	for (i = 0; i < MAX_REGULATION_NUM; ++i) {
		for (j = 0; j < MAX_2_4G_BANDWIDTH_NUM; ++j)
			for (k = 0; k < MAX_RATE_SECTION_NUM; ++k)
				for (m = 0; m < CHANNEL_MAX_NUMBER_2G; ++m)
					for (l = 0; l < MAX_RF_PATH_NUM; ++l)
						rtlphy->txpwr_limit_2_4g
								[i][j][k][m][l]
							= MAX_POWER_INDEX;
	}
	for (i = 0; i < MAX_REGULATION_NUM; ++i) {
		for (j = 0; j < MAX_5G_BANDWIDTH_NUM; ++j)
			for (k = 0; k < MAX_RATE_SECTION_NUM; ++k)
				for (m = 0; m < CHANNEL_MAX_NUMBER_5G; ++m)
					for (l = 0; l < MAX_RF_PATH_NUM; ++l)
						rtlphy->txpwr_limit_5g
								[i][j][k][m][l]
							= MAX_POWER_INDEX;
	}

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "<===== _rtl8821ae_phy_init_txpower_limit()!\n");
}