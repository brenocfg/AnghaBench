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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92d_phy_pimode_switch(struct ieee80211_hw *hw, bool pi_mode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 mode;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"BB Switch to %s mode!\n", pi_mode ? "PI" : "SI");
	mode = pi_mode ? 0x01000100 : 0x01000000;
	rtl_set_bbreg(hw, 0x820, MASKDWORD, mode);
	rtl_set_bbreg(hw, 0x828, MASKDWORD, mode);
}