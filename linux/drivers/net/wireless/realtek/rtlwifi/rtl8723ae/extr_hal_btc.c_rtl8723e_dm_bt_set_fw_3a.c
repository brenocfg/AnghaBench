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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rtl8723e_fill_h2c_cmd (struct ieee80211_hw*,int,int,int*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_set_fw_3a(struct ieee80211_hw *hw,
				     u8 byte1, u8 byte2, u8 byte3, u8 byte4,
				     u8 byte5)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[5];

	h2c_parameter[0] = byte1;
	h2c_parameter[1] = byte2;
	h2c_parameter[2] = byte3;
	h2c_parameter[3] = byte4;
	h2c_parameter[4] = byte5;
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], FW write 0x3a(4bytes)=0x%x%8x\n",
		h2c_parameter[0], h2c_parameter[1]<<24 |
		h2c_parameter[2]<<16 | h2c_parameter[3]<<8 |
		h2c_parameter[4]);
	rtl8723e_fill_h2c_cmd(hw, 0x3a, 5, h2c_parameter);
}