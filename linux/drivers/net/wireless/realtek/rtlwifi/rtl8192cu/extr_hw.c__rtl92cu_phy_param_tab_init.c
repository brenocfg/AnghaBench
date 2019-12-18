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
struct rtl_phy {TYPE_1__* hwparam_tables; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_efuse {int /*<<< orphan*/  board_type; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {void* pdata; void* length; } ;

/* Variables and functions */
 size_t AGCTAB_1T ; 
 size_t AGCTAB_2T ; 
 scalar_t__ IS_HIGHT_PA (int /*<<< orphan*/ ) ; 
 size_t MAC_REG ; 
 size_t PHY_REG_1T ; 
 size_t PHY_REG_2T ; 
 size_t PHY_REG_PG ; 
 size_t RADIOA_1T ; 
 size_t RADIOA_2T ; 
 size_t RADIOB_1T ; 
 size_t RADIOB_2T ; 
 void* RTL8192CUAGCTAB_1TARRAY ; 
 void* RTL8192CUAGCTAB_1TARRAYLENGTH ; 
 void* RTL8192CUAGCTAB_1T_HPARRAY ; 
 void* RTL8192CUAGCTAB_1T_HPARRAYLENGTH ; 
 void* RTL8192CUAGCTAB_2TARRAY ; 
 void* RTL8192CUAGCTAB_2TARRAYLENGTH ; 
 void* RTL8192CUMAC_2T_ARRAY ; 
 void* RTL8192CUMAC_2T_ARRAYLENGTH ; 
 void* RTL8192CUPHY_REG_1TARRAY ; 
 void* RTL8192CUPHY_REG_1TARRAY_LENGTH ; 
 void* RTL8192CUPHY_REG_1T_HPARRAY ; 
 void* RTL8192CUPHY_REG_1T_HPARRAYLENGTH ; 
 void* RTL8192CUPHY_REG_2TARRAY ; 
 void* RTL8192CUPHY_REG_2TARRAY_LENGTH ; 
 void* RTL8192CUPHY_REG_ARRAY_PG ; 
 void* RTL8192CUPHY_REG_ARRAY_PGLENGTH ; 
 void* RTL8192CUPHY_REG_ARRAY_PG_HP ; 
 void* RTL8192CUPHY_REG_ARRAY_PG_HPLENGTH ; 
 void* RTL8192CURADIOA_1TARRAYLENGTH ; 
 void* RTL8192CURADIOA_1T_HPARRAY ; 
 void* RTL8192CURADIOA_1T_HPARRAYLENGTH ; 
 void* RTL8192CURADIOA_2TARRAY ; 
 void* RTL8192CURADIOA_2TARRAYLENGTH ; 
 void* RTL8192CURADIOB_1TARRAYLENGTH ; 
 void* RTL8192CURADIOB_2TARRAYLENGTH ; 
 void* RTL8192CU_RADIOA_1TARRAY ; 
 void* RTL8192CU_RADIOB_1TARRAY ; 
 void* RTL8192CU_RADIOB_2TARRAY ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92cu_phy_param_tab_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);

	rtlphy->hwparam_tables[MAC_REG].length = RTL8192CUMAC_2T_ARRAYLENGTH;
	rtlphy->hwparam_tables[MAC_REG].pdata = RTL8192CUMAC_2T_ARRAY;
	if (IS_HIGHT_PA(rtlefuse->board_type)) {
		rtlphy->hwparam_tables[PHY_REG_PG].length =
			RTL8192CUPHY_REG_ARRAY_PG_HPLENGTH;
		rtlphy->hwparam_tables[PHY_REG_PG].pdata =
			RTL8192CUPHY_REG_ARRAY_PG_HP;
	} else {
		rtlphy->hwparam_tables[PHY_REG_PG].length =
			RTL8192CUPHY_REG_ARRAY_PGLENGTH;
		rtlphy->hwparam_tables[PHY_REG_PG].pdata =
			RTL8192CUPHY_REG_ARRAY_PG;
	}
	/* 2T */
	rtlphy->hwparam_tables[PHY_REG_2T].length =
			RTL8192CUPHY_REG_2TARRAY_LENGTH;
	rtlphy->hwparam_tables[PHY_REG_2T].pdata =
			RTL8192CUPHY_REG_2TARRAY;
	rtlphy->hwparam_tables[RADIOA_2T].length =
			RTL8192CURADIOA_2TARRAYLENGTH;
	rtlphy->hwparam_tables[RADIOA_2T].pdata =
			RTL8192CURADIOA_2TARRAY;
	rtlphy->hwparam_tables[RADIOB_2T].length =
			RTL8192CURADIOB_2TARRAYLENGTH;
	rtlphy->hwparam_tables[RADIOB_2T].pdata =
			RTL8192CU_RADIOB_2TARRAY;
	rtlphy->hwparam_tables[AGCTAB_2T].length =
			RTL8192CUAGCTAB_2TARRAYLENGTH;
	rtlphy->hwparam_tables[AGCTAB_2T].pdata =
			RTL8192CUAGCTAB_2TARRAY;
	/* 1T */
	if (IS_HIGHT_PA(rtlefuse->board_type)) {
		rtlphy->hwparam_tables[PHY_REG_1T].length =
			RTL8192CUPHY_REG_1T_HPARRAYLENGTH;
		rtlphy->hwparam_tables[PHY_REG_1T].pdata =
			RTL8192CUPHY_REG_1T_HPARRAY;
		rtlphy->hwparam_tables[RADIOA_1T].length =
			RTL8192CURADIOA_1T_HPARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOA_1T].pdata =
			RTL8192CURADIOA_1T_HPARRAY;
		rtlphy->hwparam_tables[RADIOB_1T].length =
			RTL8192CURADIOB_1TARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOB_1T].pdata =
			RTL8192CU_RADIOB_1TARRAY;
		rtlphy->hwparam_tables[AGCTAB_1T].length =
			RTL8192CUAGCTAB_1T_HPARRAYLENGTH;
		rtlphy->hwparam_tables[AGCTAB_1T].pdata =
			RTL8192CUAGCTAB_1T_HPARRAY;
	} else {
		rtlphy->hwparam_tables[PHY_REG_1T].length =
			 RTL8192CUPHY_REG_1TARRAY_LENGTH;
		rtlphy->hwparam_tables[PHY_REG_1T].pdata =
			RTL8192CUPHY_REG_1TARRAY;
		rtlphy->hwparam_tables[RADIOA_1T].length =
			RTL8192CURADIOA_1TARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOA_1T].pdata =
			RTL8192CU_RADIOA_1TARRAY;
		rtlphy->hwparam_tables[RADIOB_1T].length =
			RTL8192CURADIOB_1TARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOB_1T].pdata =
			RTL8192CU_RADIOB_1TARRAY;
		rtlphy->hwparam_tables[AGCTAB_1T].length =
			RTL8192CUAGCTAB_1TARRAYLENGTH;
		rtlphy->hwparam_tables[AGCTAB_1T].pdata =
			RTL8192CUAGCTAB_1TARRAY;
	}
}