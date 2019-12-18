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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASEBAND_CONFIG_PHY_REG ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int PHY_REG_ARRAY_PGLENGTH ; 
 int /*<<< orphan*/ * RTL8192CEPHY_REG_ARRAY_PG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl92c_store_pwrindex_diffrate_offset (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_addr_delay (int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool _rtl92ce_phy_config_bb_with_pgheaderfile(struct ieee80211_hw *hw,
					      u8 configtype)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int i;
	u32 *phy_regarray_table_pg;
	u16 phy_regarray_pg_len;

	phy_regarray_pg_len = PHY_REG_ARRAY_PGLENGTH;
	phy_regarray_table_pg = RTL8192CEPHY_REG_ARRAY_PG;

	if (configtype == BASEBAND_CONFIG_PHY_REG) {
		for (i = 0; i < phy_regarray_pg_len; i = i + 3) {
			rtl_addr_delay(phy_regarray_table_pg[i]);

			_rtl92c_store_pwrindex_diffrate_offset(hw,
					       phy_regarray_table_pg[i],
					       phy_regarray_table_pg[i + 1],
					       phy_regarray_table_pg[i + 2]);
		}
	} else {

		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "configtype != BaseBand_Config_PHY_REG\n");
	}
	return true;
}