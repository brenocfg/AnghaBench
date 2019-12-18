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
typedef  scalar_t__ u32 ;
struct rtl_phy {int sw_chnl_inprogress; scalar_t__ sw_chnl_step; scalar_t__ sw_chnl_stage; int /*<<< orphan*/  current_channel; scalar_t__ set_bwmode_inprogress; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int _rtl92s_phy_sw_chnl_step_by_step (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  mdelay (scalar_t__) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u8 rtl92s_phy_sw_chnl(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 delay;
	bool ret;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "switch to channel%d\n",
		 rtlphy->current_channel);

	if (rtlphy->sw_chnl_inprogress)
		return 0;

	if (rtlphy->set_bwmode_inprogress)
		return 0;

	if (is_hal_stop(rtlhal))
		return 0;

	rtlphy->sw_chnl_inprogress = true;
	rtlphy->sw_chnl_stage = 0;
	rtlphy->sw_chnl_step = 0;

	do {
		if (!rtlphy->sw_chnl_inprogress)
			break;

		ret = _rtl92s_phy_sw_chnl_step_by_step(hw,
				 rtlphy->current_channel,
				 &rtlphy->sw_chnl_stage,
				 &rtlphy->sw_chnl_step, &delay);
		if (!ret) {
			if (delay > 0)
				mdelay(delay);
			else
				continue;
		} else {
			rtlphy->sw_chnl_inprogress = false;
		}
		break;
	} while (true);

	rtlphy->sw_chnl_inprogress = false;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");

	return 1;
}