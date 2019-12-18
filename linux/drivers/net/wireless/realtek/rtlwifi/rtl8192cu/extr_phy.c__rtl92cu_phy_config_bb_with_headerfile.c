#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtl_phy {TYPE_1__* hwparam_tables; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int length; int /*<<< orphan*/ * pdata; } ;

/* Variables and functions */
 size_t AGCTAB_1T ; 
 size_t AGCTAB_2T ; 
 scalar_t__ BASEBAND_CONFIG_AGC_TAB ; 
 scalar_t__ BASEBAND_CONFIG_PHY_REG ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 size_t PHY_REG_1T ; 
 size_t PHY_REG_2T ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_addr_delay (int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool _rtl92cu_phy_config_bb_with_headerfile(struct ieee80211_hw *hw,
					    u8 configtype)
{
	int i;
	u32 *phy_regarray_table;
	u32 *agctab_array_table;
	u16 phy_reg_arraylen, agctab_arraylen;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);

	if (IS_92C_SERIAL(rtlhal->version)) {
		agctab_arraylen = rtlphy->hwparam_tables[AGCTAB_2T].length;
		agctab_array_table =  rtlphy->hwparam_tables[AGCTAB_2T].pdata;
		phy_reg_arraylen = rtlphy->hwparam_tables[PHY_REG_2T].length;
		phy_regarray_table = rtlphy->hwparam_tables[PHY_REG_2T].pdata;
	} else {
		agctab_arraylen = rtlphy->hwparam_tables[AGCTAB_1T].length;
		agctab_array_table =  rtlphy->hwparam_tables[AGCTAB_1T].pdata;
		phy_reg_arraylen = rtlphy->hwparam_tables[PHY_REG_1T].length;
		phy_regarray_table = rtlphy->hwparam_tables[PHY_REG_1T].pdata;
	}
	if (configtype == BASEBAND_CONFIG_PHY_REG) {
		for (i = 0; i < phy_reg_arraylen; i = i + 2) {
			rtl_addr_delay(phy_regarray_table[i]);
			rtl_set_bbreg(hw, phy_regarray_table[i], MASKDWORD,
				      phy_regarray_table[i + 1]);
			udelay(1);
			RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
				 "The phy_regarray_table[0] is %x Rtl819XPHY_REGARRAY[1] is %x\n",
				 phy_regarray_table[i],
				 phy_regarray_table[i + 1]);
		}
	} else if (configtype == BASEBAND_CONFIG_AGC_TAB) {
		for (i = 0; i < agctab_arraylen; i = i + 2) {
			rtl_set_bbreg(hw, agctab_array_table[i], MASKDWORD,
				      agctab_array_table[i + 1]);
			udelay(1);
			RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
				 "The agctab_array_table[0] is %x Rtl819XPHY_REGARRAY[1] is %x\n",
				 agctab_array_table[i],
				 agctab_array_table[i + 1]);
		}
	}
	return true;
}