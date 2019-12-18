#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int cnt_cck_fail; } ;
struct TYPE_3__ {scalar_t__ link_state; } ;
struct dig_t {int rssi_val_min; int cur_cck_cca_thres; int pre_cck_cca_thres; } ;
struct rtl_priv {TYPE_2__ falsealm_cnt; TYPE_1__ mac80211; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  ODM_REG_CCK_CCA_11AC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8821ae_dm_cck_packet_detection_thresh(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;
	u8 cur_cck_cca_thresh;

	if (rtlpriv->mac80211.link_state >= MAC80211_LINKED) {
		if (dm_digtable->rssi_val_min > 25) {
			cur_cck_cca_thresh = 0xcd;
		} else if ((dm_digtable->rssi_val_min <= 25) &&
			   (dm_digtable->rssi_val_min > 10)) {
			cur_cck_cca_thresh = 0x83;
		} else {
			if (rtlpriv->falsealm_cnt.cnt_cck_fail > 1000)
				cur_cck_cca_thresh = 0x83;
			else
				cur_cck_cca_thresh = 0x40;
		}
	} else {
		if (rtlpriv->falsealm_cnt.cnt_cck_fail > 1000)
			cur_cck_cca_thresh = 0x83;
		else
			cur_cck_cca_thresh = 0x40;
	}

	if (dm_digtable->cur_cck_cca_thres != cur_cck_cca_thresh)
		rtl_write_byte(rtlpriv, ODM_REG_CCK_CCA_11AC,
			       cur_cck_cca_thresh);

	dm_digtable->pre_cck_cca_thres = dm_digtable->cur_cck_cca_thres;
	dm_digtable->cur_cck_cca_thres = cur_cck_cca_thresh;
	RT_TRACE(rtlpriv, COMP_DIG, DBG_TRACE,
		 "CCK cca thresh hold =%x\n", dm_digtable->cur_cck_cca_thres);
}