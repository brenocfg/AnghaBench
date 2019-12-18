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
struct rtl_priv {int dummy; } ;
struct rtl_ep_map {int* ep_mapping; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 size_t RTL_TXQ_BCN ; 
 size_t RTL_TXQ_BE ; 
 size_t RTL_TXQ_BK ; 
 size_t RTL_TXQ_HI ; 
 size_t RTL_TXQ_MGT ; 
 size_t RTL_TXQ_VI ; 
 size_t RTL_TXQ_VO ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void threeoutepmapping(struct ieee80211_hw *hw, bool  bwificfg,
			       struct rtl_ep_map *ep_map)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (bwificfg) { /* for WMM */
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG,
			 "USB 3EP Setting for WMM.....\n");
		ep_map->ep_mapping[RTL_TXQ_BE]	= 5;
		ep_map->ep_mapping[RTL_TXQ_BK]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VI]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VO]	= 2;
		ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
		ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
		ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
	} else { /* typical setting */
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG,
			 "USB 3EP Setting for typical.....\n");
		ep_map->ep_mapping[RTL_TXQ_BE]	= 5;
		ep_map->ep_mapping[RTL_TXQ_BK]	= 5;
		ep_map->ep_mapping[RTL_TXQ_VI]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VO]	= 2;
		ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
		ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
		ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
	}
}