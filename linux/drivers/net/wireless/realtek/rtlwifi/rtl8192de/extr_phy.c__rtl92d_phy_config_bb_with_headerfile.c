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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {scalar_t__ interfaceindex; scalar_t__ current_bandtype; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int AGCTAB_2G_ARRAYLENGTH ; 
 int AGCTAB_5G_ARRAYLENGTH ; 
 int AGCTAB_ARRAYLENGTH ; 
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BASEBAND_CONFIG_AGC_TAB ; 
 scalar_t__ BASEBAND_CONFIG_PHY_REG ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int PHY_REG_2T_ARRAYLENGTH ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * rtl8192de_agctab_2garray ; 
 int /*<<< orphan*/ * rtl8192de_agctab_5garray ; 
 int /*<<< orphan*/ * rtl8192de_agctab_array ; 
 int /*<<< orphan*/ * rtl8192de_phy_reg_2tarray ; 
 int /*<<< orphan*/  rtl_addr_delay (int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool _rtl92d_phy_config_bb_with_headerfile(struct ieee80211_hw *hw,
	u8 configtype)
{
	int i;
	u32 *phy_regarray_table;
	u32 *agctab_array_table = NULL;
	u32 *agctab_5garray_table;
	u16 phy_reg_arraylen, agctab_arraylen = 0, agctab_5garraylen;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	/* Normal chip,Mac0 use AGC_TAB.txt for 2G and 5G band. */
	if (rtlhal->interfaceindex == 0) {
		agctab_arraylen = AGCTAB_ARRAYLENGTH;
		agctab_array_table = rtl8192de_agctab_array;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 " ===> phy:MAC0, Rtl819XAGCTAB_Array\n");
	} else {
		if (rtlhal->current_bandtype == BAND_ON_2_4G) {
			agctab_arraylen = AGCTAB_2G_ARRAYLENGTH;
			agctab_array_table = rtl8192de_agctab_2garray;
			RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
				 " ===> phy:MAC1, Rtl819XAGCTAB_2GArray\n");
		} else {
			agctab_5garraylen = AGCTAB_5G_ARRAYLENGTH;
			agctab_5garray_table = rtl8192de_agctab_5garray;
			RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
				 " ===> phy:MAC1, Rtl819XAGCTAB_5GArray\n");

		}
	}
	phy_reg_arraylen = PHY_REG_2T_ARRAYLENGTH;
	phy_regarray_table = rtl8192de_phy_reg_2tarray;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 " ===> phy:Rtl819XPHY_REG_Array_PG\n");
	if (configtype == BASEBAND_CONFIG_PHY_REG) {
		for (i = 0; i < phy_reg_arraylen; i = i + 2) {
			rtl_addr_delay(phy_regarray_table[i]);
			rtl_set_bbreg(hw, phy_regarray_table[i], MASKDWORD,
				      phy_regarray_table[i + 1]);
			udelay(1);
			RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
				 "The phy_regarray_table[0] is %x Rtl819XPHY_REGArray[1] is %x\n",
				 phy_regarray_table[i],
				 phy_regarray_table[i + 1]);
		}
	} else if (configtype == BASEBAND_CONFIG_AGC_TAB) {
		if (rtlhal->interfaceindex == 0) {
			for (i = 0; i < agctab_arraylen; i = i + 2) {
				rtl_set_bbreg(hw, agctab_array_table[i],
					MASKDWORD,
					agctab_array_table[i + 1]);
				/* Add 1us delay between BB/RF register
				 * setting. */
				udelay(1);
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					 "The Rtl819XAGCTAB_Array_Table[0] is %u Rtl819XPHY_REGArray[1] is %u\n",
					 agctab_array_table[i],
					 agctab_array_table[i + 1]);
			}
			RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
				 "Normal Chip, MAC0, load Rtl819XAGCTAB_Array\n");
		} else {
			if (rtlhal->current_bandtype == BAND_ON_2_4G) {
				for (i = 0; i < agctab_arraylen; i = i + 2) {
					rtl_set_bbreg(hw, agctab_array_table[i],
						MASKDWORD,
						agctab_array_table[i + 1]);
					/* Add 1us delay between BB/RF register
					 * setting. */
					udelay(1);
					RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
						 "The Rtl819XAGCTAB_Array_Table[0] is %u Rtl819XPHY_REGArray[1] is %u\n",
						 agctab_array_table[i],
						 agctab_array_table[i + 1]);
				}
				RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
					 "Load Rtl819XAGCTAB_2GArray\n");
			} else {
				for (i = 0; i < agctab_5garraylen; i = i + 2) {
					rtl_set_bbreg(hw,
						agctab_5garray_table[i],
						MASKDWORD,
						agctab_5garray_table[i + 1]);
					/* Add 1us delay between BB/RF registeri
					 * setting. */
					udelay(1);
					RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
						 "The Rtl819XAGCTAB_5GArray_Table[0] is %u Rtl819XPHY_REGArray[1] is %u\n",
						 agctab_5garray_table[i],
						 agctab_5garray_table[i + 1]);
				}
				RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
					 "Load Rtl819XAGCTAB_5GArray\n");
			}
		}
	}
	return true;
}