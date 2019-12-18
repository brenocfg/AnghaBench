#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_16__ {int cfo_threshold; scalar_t__ crystal_cap; } ;
struct TYPE_15__ {scalar_t__ rf_type; } ;
struct TYPE_14__ {int crystalcap; } ;
struct TYPE_13__ {TYPE_4__* btc_ops; } ;
struct TYPE_9__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_8__ dm; TYPE_7__ phy; TYPE_6__ efuse; TYPE_5__ btcoexist; TYPE_3__* cfg; TYPE_1__ mac80211; } ;
struct rtl_dm {int atc_status; int crystal_cap; int* cfo_tail; scalar_t__ packet_count; scalar_t__ packet_count_pre; int cfo_ave_pre; int large_cfo_hit; int cfo_threshold; int is_freeze; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* btc_is_bt_disabled ) (struct rtl_priv*) ;} ;
struct TYPE_11__ {TYPE_2__* ops; } ;
struct TYPE_10__ {scalar_t__ (* get_btc_status ) () ;} ;

/* Variables and functions */
 int ATC_STATUS_OFF ; 
 int ATC_STATUS_ON ; 
 int BIT (int) ; 
 int CFO_THRESHOLD_ATC ; 
 int CFO_THRESHOLD_XTAL ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  REG_MAC_PHY_CTRL ; 
 scalar_t__ RF_1T1R ; 
 int /*<<< orphan*/  ROFDM1_CFOTRACKING ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*) ; 

__attribute__((used)) static void rtl92ee_dm_dynamic_atc_switch(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 crystal_cap;
	u32 packet_count;
	int cfo_khz_a , cfo_khz_b , cfo_ave = 0, adjust_xtal = 0;
	int cfo_ave_diff;

	if (rtlpriv->mac80211.link_state < MAC80211_LINKED) {
		if (rtldm->atc_status == ATC_STATUS_OFF) {
			rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11),
				      ATC_STATUS_ON);
			rtldm->atc_status = ATC_STATUS_ON;
		}
		/* Disable CFO tracking for BT */
		if (rtlpriv->cfg->ops->get_btc_status()) {
			if (!rtlpriv->btcoexist.btc_ops->
			    btc_is_bt_disabled(rtlpriv)) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "odm_DynamicATCSwitch(): Disable CFO tracking for BT!!\n");
				return;
			}
		}
		/* Reset Crystal Cap */
		if (rtldm->crystal_cap != rtlpriv->efuse.crystalcap) {
			rtldm->crystal_cap = rtlpriv->efuse.crystalcap;
			crystal_cap = rtldm->crystal_cap & 0x3f;
			rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
				      (crystal_cap | (crystal_cap << 6)));
		}
	} else {
		cfo_khz_a = (int)(rtldm->cfo_tail[0] * 3125) / 1280;
		cfo_khz_b = (int)(rtldm->cfo_tail[1] * 3125) / 1280;
		packet_count = rtldm->packet_count;

		if (packet_count == rtldm->packet_count_pre)
			return;

		rtldm->packet_count_pre = packet_count;

		if (rtlpriv->phy.rf_type == RF_1T1R)
			cfo_ave = cfo_khz_a;
		else
			cfo_ave = (int)(cfo_khz_a + cfo_khz_b) >> 1;

		cfo_ave_diff = (rtldm->cfo_ave_pre >= cfo_ave) ?
			       (rtldm->cfo_ave_pre - cfo_ave) :
			       (cfo_ave - rtldm->cfo_ave_pre);

		if (cfo_ave_diff > 20 && rtldm->large_cfo_hit == 0) {
			rtldm->large_cfo_hit = 1;
			return;
		}
		rtldm->large_cfo_hit = 0;

		rtldm->cfo_ave_pre = cfo_ave;

		if (cfo_ave >= -rtldm->cfo_threshold &&
		    cfo_ave <= rtldm->cfo_threshold && rtldm->is_freeze == 0) {
			if (rtldm->cfo_threshold == CFO_THRESHOLD_XTAL) {
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL + 10;
				rtldm->is_freeze = 1;
			} else {
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL;
			}
		}

		if (cfo_ave > rtldm->cfo_threshold && rtldm->crystal_cap < 0x3f)
			adjust_xtal = ((cfo_ave - CFO_THRESHOLD_XTAL) >> 2) + 1;
		else if ((cfo_ave < -rtlpriv->dm.cfo_threshold) &&
			 rtlpriv->dm.crystal_cap > 0)
			adjust_xtal = ((cfo_ave + CFO_THRESHOLD_XTAL) >> 2) - 1;

		if (adjust_xtal != 0) {
			rtldm->is_freeze = 0;
			rtldm->crystal_cap += adjust_xtal;

			if (rtldm->crystal_cap > 0x3f)
				rtldm->crystal_cap = 0x3f;
			else if (rtldm->crystal_cap < 0)
				rtldm->crystal_cap = 0;

			crystal_cap = rtldm->crystal_cap & 0x3f;
			rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
				      (crystal_cap | (crystal_cap << 6)));
		}

		if (cfo_ave < CFO_THRESHOLD_ATC &&
		    cfo_ave > -CFO_THRESHOLD_ATC) {
			if (rtldm->atc_status == ATC_STATUS_ON) {
				rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11),
					      ATC_STATUS_OFF);
				rtldm->atc_status = ATC_STATUS_OFF;
			}
		} else {
			if (rtldm->atc_status == ATC_STATUS_OFF) {
				rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11),
					      ATC_STATUS_ON);
				rtldm->atc_status = ATC_STATUS_ON;
			}
		}
	}
}