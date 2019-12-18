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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__* internal_pa_5g; } ;
struct rtl_priv {TYPE_1__ efuse; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rf_content { ____Placeholder_rf_content } rf_content ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int RADIOA_2T_ARRAYLENGTH ; 
 int RADIOA_2T_INT_PA_ARRAYLENGTH ; 
 int RADIOB_2T_ARRAYLENGTH ; 
 int RADIOB_2T_INT_PA_ARRAYLENGTH ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int radiob_txt ; 
 int /*<<< orphan*/ * rtl8192de_radioa_2t_int_paarray ; 
 int /*<<< orphan*/ * rtl8192de_radioa_2tarray ; 
 int /*<<< orphan*/ * rtl8192de_radiob_2t_int_paarray ; 
 int /*<<< orphan*/ * rtl8192de_radiob_2tarray ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_rfreg_delay (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool rtl92d_phy_config_rf_with_headerfile(struct ieee80211_hw *hw,
					  enum rf_content content,
					  enum radio_path rfpath)
{
	int i;
	u32 *radioa_array_table;
	u32 *radiob_array_table;
	u16 radioa_arraylen, radiob_arraylen;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	radioa_arraylen = RADIOA_2T_ARRAYLENGTH;
	radioa_array_table = rtl8192de_radioa_2tarray;
	radiob_arraylen = RADIOB_2T_ARRAYLENGTH;
	radiob_array_table = rtl8192de_radiob_2tarray;
	if (rtlpriv->efuse.internal_pa_5g[0]) {
		radioa_arraylen = RADIOA_2T_INT_PA_ARRAYLENGTH;
		radioa_array_table = rtl8192de_radioa_2t_int_paarray;
	}
	if (rtlpriv->efuse.internal_pa_5g[1]) {
		radiob_arraylen = RADIOB_2T_INT_PA_ARRAYLENGTH;
		radiob_array_table = rtl8192de_radiob_2t_int_paarray;
	}
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "PHY_ConfigRFWithHeaderFile() Radio_A:Rtl819XRadioA_1TArray\n");
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "PHY_ConfigRFWithHeaderFile() Radio_B:Rtl819XRadioB_1TArray\n");
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "Radio No %x\n", rfpath);

	/* this only happens when DMDP, mac0 start on 2.4G,
	 * mac1 start on 5G, mac 0 has to set phy0&phy1
	 * pathA or mac1 has to set phy0&phy1 pathA */
	if ((content == radiob_txt) && (rfpath == RF90_PATH_A)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 " ===> althougth Path A, we load radiob.txt\n");
		radioa_arraylen = radiob_arraylen;
		radioa_array_table = radiob_array_table;
	}
	switch (rfpath) {
	case RF90_PATH_A:
		for (i = 0; i < radioa_arraylen; i = i + 2) {
			rtl_rfreg_delay(hw, rfpath, radioa_array_table[i],
					RFREG_OFFSET_MASK,
					radioa_array_table[i + 1]);
		}
		break;
	case RF90_PATH_B:
		for (i = 0; i < radiob_arraylen; i = i + 2) {
			rtl_rfreg_delay(hw, rfpath, radiob_array_table[i],
					RFREG_OFFSET_MASK,
					radiob_array_table[i + 1]);
		}
		break;
	case RF90_PATH_C:
	case RF90_PATH_D:
		pr_err("switch case %#x not processed\n", rfpath);
		break;
	}
	return true;
}