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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ bt_coexist_type; int bt_ant_isolation; scalar_t__ bt_service; scalar_t__ bt_coexistence; } ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {TYPE_1__ btcoexist; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT_OFFSET_LEN_MASK_32 (int,int) ; 
 scalar_t__ BT_CSR_BC4 ; 
 scalar_t__ BT_CSR_BC8 ; 
 scalar_t__ BT_SCO ; 
 scalar_t__ REG_BT_COEX_TABLE ; 
 int REG_GPIO_MUXCFG ; 
 scalar_t__ RF_1T1R ; 
 int ROFDM0_TRXPATHENABLE ; 
 int ROFDM1_TRXPATHENABLE ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 

void rtl8192ce_bt_hw_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);

	u8 u1_tmp;

	if (rtlpriv->btcoexist.bt_coexistence &&
	    ((rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4) ||
	      rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC8)) {

		if (rtlpriv->btcoexist.bt_ant_isolation)
			rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);

		u1_tmp = rtl_read_byte(rtlpriv, 0x4fd) &
			 BIT_OFFSET_LEN_MASK_32(0, 1);
		u1_tmp = u1_tmp |
			 ((rtlpriv->btcoexist.bt_ant_isolation == 1) ?
			 0 : BIT_OFFSET_LEN_MASK_32(1, 1)) |
			 ((rtlpriv->btcoexist.bt_service == BT_SCO) ?
			 0 : BIT_OFFSET_LEN_MASK_32(2, 1));
		rtl_write_byte(rtlpriv, 0x4fd, u1_tmp);

		rtl_write_dword(rtlpriv, REG_BT_COEX_TABLE+4, 0xaaaa9aaa);
		rtl_write_dword(rtlpriv, REG_BT_COEX_TABLE+8, 0xffbd0040);
		rtl_write_dword(rtlpriv, REG_BT_COEX_TABLE+0xc, 0x40000010);

		/* Config to 1T1R. */
		if (rtlphy->rf_type == RF_1T1R) {
			u1_tmp = rtl_read_byte(rtlpriv, ROFDM0_TRXPATHENABLE);
			u1_tmp &= ~(BIT_OFFSET_LEN_MASK_32(1, 1));
			rtl_write_byte(rtlpriv, ROFDM0_TRXPATHENABLE, u1_tmp);

			u1_tmp = rtl_read_byte(rtlpriv, ROFDM1_TRXPATHENABLE);
			u1_tmp &= ~(BIT_OFFSET_LEN_MASK_32(1, 1));
			rtl_write_byte(rtlpriv, ROFDM1_TRXPATHENABLE, u1_tmp);
		}
	}
}