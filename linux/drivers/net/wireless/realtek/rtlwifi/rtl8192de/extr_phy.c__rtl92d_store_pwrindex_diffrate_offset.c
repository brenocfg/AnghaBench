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
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ RTXAGC_A_CCK1_MCS32 ; 
 scalar_t__ RTXAGC_A_MCS03_MCS00 ; 
 scalar_t__ RTXAGC_A_MCS07_MCS04 ; 
 scalar_t__ RTXAGC_A_MCS11_MCS08 ; 
 scalar_t__ RTXAGC_A_MCS15_MCS12 ; 
 scalar_t__ RTXAGC_A_RATE18_06 ; 
 scalar_t__ RTXAGC_A_RATE54_24 ; 
 scalar_t__ RTXAGC_B_CCK11_A_CCK2_11 ; 
 scalar_t__ RTXAGC_B_CCK1_55_MCS32 ; 
 scalar_t__ RTXAGC_B_MCS03_MCS00 ; 
 scalar_t__ RTXAGC_B_MCS07_MCS04 ; 
 scalar_t__ RTXAGC_B_MCS11_MCS08 ; 
 scalar_t__ RTXAGC_B_MCS15_MCS12 ; 
 scalar_t__ RTXAGC_B_RATE18_06 ; 
 scalar_t__ RTXAGC_B_RATE54_24 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92d_store_pwrindex_diffrate_offset(struct ieee80211_hw *hw,
						   u32 regaddr, u32 bitmask,
						   u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	int index;

	if (regaddr == RTXAGC_A_RATE18_06)
		index = 0;
	else if (regaddr == RTXAGC_A_RATE54_24)
		index = 1;
	else if (regaddr == RTXAGC_A_CCK1_MCS32)
		index = 6;
	else if (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && bitmask == 0xffffff00)
		index = 7;
	else if (regaddr == RTXAGC_A_MCS03_MCS00)
		index = 2;
	else if (regaddr == RTXAGC_A_MCS07_MCS04)
		index = 3;
	else if (regaddr == RTXAGC_A_MCS11_MCS08)
		index = 4;
	else if (regaddr == RTXAGC_A_MCS15_MCS12)
		index = 5;
	else if (regaddr == RTXAGC_B_RATE18_06)
		index = 8;
	else if (regaddr == RTXAGC_B_RATE54_24)
		index = 9;
	else if (regaddr == RTXAGC_B_CCK1_55_MCS32)
		index = 14;
	else if (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && bitmask == 0x000000ff)
		index = 15;
	else if (regaddr == RTXAGC_B_MCS03_MCS00)
		index = 10;
	else if (regaddr == RTXAGC_B_MCS07_MCS04)
		index = 11;
	else if (regaddr == RTXAGC_B_MCS11_MCS08)
		index = 12;
	else if (regaddr == RTXAGC_B_MCS15_MCS12)
		index = 13;
	else
		return;

	rtlphy->mcs_offset[rtlphy->pwrgroup_cnt][index] = data;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
		 "MCSTxPowerLevelOriginalOffset[%d][%d] = 0x%x\n",
		 rtlphy->pwrgroup_cnt, index,
		 rtlphy->mcs_offset[rtlphy->pwrgroup_cnt][index]);
	if (index == 13)
		rtlphy->pwrgroup_cnt++;
}