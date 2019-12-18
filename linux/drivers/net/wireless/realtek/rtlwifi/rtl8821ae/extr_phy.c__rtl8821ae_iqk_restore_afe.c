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
typedef  size_t u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  COMP_IQK ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 

__attribute__((used)) static void _rtl8821ae_iqk_restore_afe(struct ieee80211_hw *hw,
				       u32 *afe_backup, u32 *backup_afe_reg,
				       u32 afe_num)
{
	u32 i;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
	/* Reload AFE Parameters */
	for (i = 0; i < afe_num; i++)
		rtl_write_dword(rtlpriv, backup_afe_reg[i], afe_backup[i]);
	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
	rtl_write_dword(rtlpriv, 0xc80, 0x0);
	rtl_write_dword(rtlpriv, 0xc84, 0x0);
	rtl_write_dword(rtlpriv, 0xc88, 0x0);
	rtl_write_dword(rtlpriv, 0xc8c, 0x3c000000);
	rtl_write_dword(rtlpriv, 0xc90, 0x00000080);
	rtl_write_dword(rtlpriv, 0xc94, 0x00000000);
	rtl_write_dword(rtlpriv, 0xcc4, 0x20040000);
	rtl_write_dword(rtlpriv, 0xcc8, 0x20000000);
	rtl_write_dword(rtlpriv, 0xcb8, 0x0);
	RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD, "RestoreAFE Success!!!!\n");
}