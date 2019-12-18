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
 size_t rtl_read_dword (struct rtl_priv*,size_t) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl8821ae_iqk_backup_afe(struct ieee80211_hw *hw, u32 *afe_backup,
				      u32 *backup_afe_REG, u32 afe_num)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
	/*Save AFE Parameters */
	for (i = 0; i < afe_num; i++)
		afe_backup[i] = rtl_read_dword(rtlpriv, backup_afe_REG[i]);
	RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD, "BackupAFE Success!!!!\n");
}