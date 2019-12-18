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
typedef  scalar_t__ u32 ;
struct rtl_phy {size_t pwrgroup_cnt; scalar_t__** mcs_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTXAGC_CCK_MCS32 ; 
 scalar_t__ RTXAGC_MCS03_MCS00 ; 
 scalar_t__ RTXAGC_MCS07_MCS04 ; 
 scalar_t__ RTXAGC_MCS11_MCS08 ; 
 scalar_t__ RTXAGC_MCS15_MCS12 ; 
 scalar_t__ RTXAGC_RATE18_06 ; 
 scalar_t__ RTXAGC_RATE54_24 ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_store_pwrindex_diffrate_offset(struct ieee80211_hw *hw,
		u32 reg_addr, u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	int index;

	if (reg_addr == RTXAGC_RATE18_06)
		index = 0;
	else if (reg_addr == RTXAGC_RATE54_24)
		index = 1;
	else if (reg_addr == RTXAGC_CCK_MCS32)
		index = 6;
	else if (reg_addr == RTXAGC_MCS03_MCS00)
		index = 2;
	else if (reg_addr == RTXAGC_MCS07_MCS04)
		index = 3;
	else if (reg_addr == RTXAGC_MCS11_MCS08)
		index = 4;
	else if (reg_addr == RTXAGC_MCS15_MCS12)
		index = 5;
	else
		return;

	rtlphy->mcs_offset[rtlphy->pwrgroup_cnt][index] = data;
	if (index == 5)
		rtlphy->pwrgroup_cnt++;
}