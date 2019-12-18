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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ HARDWARE_TYPE_RTL8821AE ; 
 int /*<<< orphan*/  RTL8812AE_MAC_1T_ARRAYLEN ; 
 int /*<<< orphan*/ * RTL8812AE_MAC_REG_ARRAY ; 
 int /*<<< orphan*/  RTL8821AE_MAC_1T_ARRAYLEN ; 
 int /*<<< orphan*/ * RTL8821AE_MAC_REG_ARRAY ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int __rtl8821ae_phy_config_with_headerfile (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte_with_val32 ; 

__attribute__((used)) static bool _rtl8821ae_phy_config_mac_with_headerfile(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 arraylength;
	u32 *ptrarray;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "Read MAC_REG_Array\n");
	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
		arraylength = RTL8821AE_MAC_1T_ARRAYLEN;
		ptrarray = RTL8821AE_MAC_REG_ARRAY;
	} else {
		arraylength = RTL8812AE_MAC_1T_ARRAYLEN;
		ptrarray = RTL8812AE_MAC_REG_ARRAY;
	}
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "Img: MAC_REG_ARRAY LEN %d\n", arraylength);

	return __rtl8821ae_phy_config_with_headerfile(hw,
			ptrarray, arraylength, rtl_write_byte_with_val32);
}