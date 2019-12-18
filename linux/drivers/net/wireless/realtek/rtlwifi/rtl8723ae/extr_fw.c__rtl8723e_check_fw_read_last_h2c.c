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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_HMETFR ; 
 scalar_t__ REG_MCUTST_1 ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ rtl_read_byte (struct rtl_priv*,scalar_t__) ; 

__attribute__((used)) static bool _rtl8723e_check_fw_read_last_h2c(struct ieee80211_hw *hw,
					     u8 boxnum)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 val_hmetfr, val_mcutst_1;
	bool result = false;

	val_hmetfr = rtl_read_byte(rtlpriv, REG_HMETFR);
	val_mcutst_1 = rtl_read_byte(rtlpriv, (REG_MCUTST_1 + boxnum));

	if (((val_hmetfr >> boxnum) & BIT(0)) == 0 && val_mcutst_1 == 0)
		result = true;
	return result;
}