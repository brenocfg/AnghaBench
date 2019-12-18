#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_10__ {scalar_t__ hw_type; } ;
struct TYPE_9__ {int cfo_threshold; scalar_t__ crystal_cap; } ;
struct TYPE_8__ {scalar_t__ rf_type; } ;
struct TYPE_7__ {int crystalcap; } ;
struct TYPE_6__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_5__ rtlhal; TYPE_4__ dm; TYPE_3__ phy; TYPE_2__ efuse; TYPE_1__ mac80211; } ;
struct rtl_dm {scalar_t__ atc_status; int crystal_cap; int* cfo_tail; scalar_t__ packet_count; scalar_t__ packet_count_pre; int cfo_ave_pre; int large_cfo_hit; int cfo_threshold; int is_freeze; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATC_STATUS_OFF ; 
 int ATC_STATUS_ON ; 
 int BIT (int) ; 
 int CFO_THRESHOLD_XTAL ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  REG_MAC_PHY_CTRL ; 
 int /*<<< orphan*/  RFC_AREA ; 
 scalar_t__ RF_1T1R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl8821ae_dm_dynamic_atc_switch(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 crystal_cap;
	u32 packet_count;
	int cfo_khz_a, cfo_khz_b, cfo_ave = 0, adjust_xtal = 0;
	int cfo_ave_diff;

	if (rtlpriv->mac80211.link_state < MAC80211_LINKED) {
		/*1.Enable ATC*/
		if (rtldm->atc_status == ATC_STATUS_OFF) {
			rtl_set_bbreg(hw, RFC_AREA, BIT(14), ATC_STATUS_ON);
			rtldm->atc_status = ATC_STATUS_ON;
		}

		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "No link!!\n");
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "atc_status = %d\n", rtldm->atc_status);

		if (rtldm->crystal_cap != rtlpriv->efuse.crystalcap) {
			rtldm->crystal_cap = rtlpriv->efuse.crystalcap;
			crystal_cap = rtldm->crystal_cap & 0x3f;
			crystal_cap = crystal_cap & 0x3f;
			if (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8812AE)
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0x7ff80000, (crystal_cap |
					      (crystal_cap << 6)));
			else
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0xfff000, (crystal_cap |
					      (crystal_cap << 6)));
		}
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "crystal_cap = 0x%x\n",
			 rtldm->crystal_cap);
	} else{
		/*1. Calculate CFO for path-A & path-B*/
		cfo_khz_a = (int)(rtldm->cfo_tail[0] * 3125) / 1280;
		cfo_khz_b = (int)(rtldm->cfo_tail[1] * 3125) / 1280;
		packet_count = rtldm->packet_count;

		/*2.No new packet*/
		if (packet_count == rtldm->packet_count_pre) {
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "packet counter doesn't change\n");
			return;
		}

		rtldm->packet_count_pre = packet_count;
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "packet counter = %d\n",
			 rtldm->packet_count);

		/*3.Average CFO*/
		if (rtlpriv->phy.rf_type == RF_1T1R)
			cfo_ave = cfo_khz_a;
		else
			cfo_ave = (cfo_khz_a + cfo_khz_b) >> 1;

		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "cfo_khz_a = %dkHz, cfo_khz_b = %dkHz, cfo_ave = %dkHz\n",
			 cfo_khz_a, cfo_khz_b, cfo_ave);

		/*4.Avoid abnormal large CFO*/
		cfo_ave_diff = (rtldm->cfo_ave_pre >= cfo_ave) ?
						(rtldm->cfo_ave_pre - cfo_ave) :
						(cfo_ave - rtldm->cfo_ave_pre);

		if (cfo_ave_diff > 20 && rtldm->large_cfo_hit == 0) {
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "first large CFO hit\n");
			rtldm->large_cfo_hit = 1;
			return;
		} else
			rtldm->large_cfo_hit = 0;

		rtldm->cfo_ave_pre = cfo_ave;

		/*CFO tracking by adjusting Xtal cap.*/

		/*1.Dynamic Xtal threshold*/
		if (cfo_ave >= -rtldm->cfo_threshold &&
			cfo_ave <= rtldm->cfo_threshold &&
			rtldm->is_freeze == 0) {
			if (rtldm->cfo_threshold == CFO_THRESHOLD_XTAL) {
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL + 10;
				rtldm->is_freeze = 1;
			} else {
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL;
			}
		}
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "Dynamic threshold = %d\n",
			 rtldm->cfo_threshold);

		/* 2.Calculate Xtal offset*/
		if (cfo_ave > rtldm->cfo_threshold && rtldm->crystal_cap < 0x3f)
			adjust_xtal = ((cfo_ave - CFO_THRESHOLD_XTAL) >> 2) + 1;
		else if ((cfo_ave < -rtlpriv->dm.cfo_threshold) &&
			 rtlpriv->dm.crystal_cap > 0)
			adjust_xtal = ((cfo_ave + CFO_THRESHOLD_XTAL) >> 2) - 1;
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "Crystal cap = 0x%x, Crystal cap offset = %d\n",
			 rtldm->crystal_cap, adjust_xtal);

		/*3.Adjudt Crystal Cap.*/
		if (adjust_xtal != 0) {
			rtldm->is_freeze = 0;
			rtldm->crystal_cap += adjust_xtal;

			if (rtldm->crystal_cap > 0x3f)
				rtldm->crystal_cap = 0x3f;
			else if (rtldm->crystal_cap < 0)
				rtldm->crystal_cap = 0;

			crystal_cap = rtldm->crystal_cap & 0x3f;
			crystal_cap = crystal_cap & 0x3f;
			if (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8812AE)
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0x7ff80000, (crystal_cap |
					      (crystal_cap << 6)));
			else
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0xfff000, (crystal_cap |
					      (crystal_cap << 6)));
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "New crystal cap = 0x%x\n",
				 rtldm->crystal_cap);
		}
	}
}