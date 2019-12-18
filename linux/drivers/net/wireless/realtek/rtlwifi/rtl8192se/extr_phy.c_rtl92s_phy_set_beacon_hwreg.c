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
typedef  int u32 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ WFM3 ; 
 scalar_t__ WFM5 ; 
 int hal_get_firmwareversion (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 

void rtl92s_phy_set_beacon_hwreg(struct ieee80211_hw *hw, u16 beaconinterval)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 new_bcn_num = 0;

	if (hal_get_firmwareversion(rtlpriv) >= 0x33) {
		/* Fw v.51 and later. */
		rtl_write_dword(rtlpriv, WFM5, 0xF1000000 |
				(beaconinterval << 8));
	} else {
		new_bcn_num = beaconinterval * 32 - 64;
		rtl_write_dword(rtlpriv, WFM3 + 4, new_bcn_num);
		rtl_write_dword(rtlpriv, WFM3, 0xB026007C);
	}
}