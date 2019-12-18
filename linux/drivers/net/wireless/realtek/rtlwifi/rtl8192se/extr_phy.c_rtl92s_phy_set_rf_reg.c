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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rf_lock; } ;
struct rtl_phy {int rf_pathmap; } ;
struct rtl_priv {TYPE_1__ locks; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int _rtl92s_phy_calculate_bit_shift (int) ; 
 int _rtl92s_phy_rf_serial_read (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  _rtl92s_phy_rf_serial_write (struct ieee80211_hw*,int,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rtl92s_phy_set_rf_reg(struct ieee80211_hw *hw, enum radio_path rfpath,
			   u32 regaddr, u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 original_value, bitshift;

	if (!((rtlphy->rf_pathmap >> rfpath) & 0x1))
		return;

	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
		 "regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		 regaddr, bitmask, data, rfpath);

	spin_lock(&rtlpriv->locks.rf_lock);

	if (bitmask != RFREG_OFFSET_MASK) {
		original_value = _rtl92s_phy_rf_serial_read(hw, rfpath,
							    regaddr);
		bitshift = _rtl92s_phy_calculate_bit_shift(bitmask);
		data = ((original_value & (~bitmask)) | (data << bitshift));
	}

	_rtl92s_phy_rf_serial_write(hw, rfpath, regaddr, data);

	spin_unlock(&rtlpriv->locks.rf_lock);

	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
		 "regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		 regaddr, bitmask, data, rfpath);

}