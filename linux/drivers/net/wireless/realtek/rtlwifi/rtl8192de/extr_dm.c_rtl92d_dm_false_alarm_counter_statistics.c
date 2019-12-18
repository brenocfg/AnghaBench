#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ current_bandtype; } ;
struct false_alarm_statistics {int cnt_fast_fsync_fail; int cnt_sb_search_fail; int cnt_parity_fail; int cnt_rate_illegal; int cnt_crc8_fail; int cnt_mcs_fail; int cnt_ofdm_fail; int cnt_cck_fail; int cnt_all; } ;
struct rtl_priv {TYPE_1__ rtlhal; struct false_alarm_statistics falsealm_cnt; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_5G ; 
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  MASKBYTE3 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RCCK0_FACOUNTERLOWER ; 
 int /*<<< orphan*/  RCCK0_FACOUNTERUPPER ; 
 int /*<<< orphan*/  RCCK0_FALSEALARMREPORT ; 
 int /*<<< orphan*/  ROFDM0_FRAMESYNC ; 
 int /*<<< orphan*/  ROFDM0_LSTF ; 
 int /*<<< orphan*/  ROFDM1_LSTF ; 
 int /*<<< orphan*/  ROFDM_PHYCOUNTER1 ; 
 int /*<<< orphan*/  ROFDM_PHYCOUNTER2 ; 
 int /*<<< orphan*/  ROFDM_PHYCOUNTER3 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  rtl92d_acquire_cckandrw_pagea_ctl (struct ieee80211_hw*,unsigned long*) ; 
 int /*<<< orphan*/  rtl92d_release_cckandrw_pagea_ctl (struct ieee80211_hw*,unsigned long*) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl92d_dm_false_alarm_counter_statistics(struct ieee80211_hw *hw)
{
	u32 ret_value;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);
	unsigned long flag = 0;

	/* hold ofdm counter */
	rtl_set_bbreg(hw, ROFDM0_LSTF, BIT(31), 1); /* hold page C counter */
	rtl_set_bbreg(hw, ROFDM1_LSTF, BIT(31), 1); /*hold page D counter */

	ret_value = rtl_get_bbreg(hw, ROFDM0_FRAMESYNC, MASKDWORD);
	falsealm_cnt->cnt_fast_fsync_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_sb_search_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER1, MASKDWORD);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER2, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER3, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
				      falsealm_cnt->cnt_rate_illegal +
				      falsealm_cnt->cnt_crc8_fail +
				      falsealm_cnt->cnt_mcs_fail +
				      falsealm_cnt->cnt_fast_fsync_fail +
				      falsealm_cnt->cnt_sb_search_fail;

	if (rtlpriv->rtlhal.current_bandtype != BAND_ON_5G) {
		/* hold cck counter */
		rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
		ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERLOWER, MASKBYTE0);
		falsealm_cnt->cnt_cck_fail = ret_value;
		ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERUPPER, MASKBYTE3);
		falsealm_cnt->cnt_cck_fail += (ret_value & 0xff) << 8;
		rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
	} else {
		falsealm_cnt->cnt_cck_fail = 0;
	}

	/* reset false alarm counter registers */
	falsealm_cnt->cnt_all = falsealm_cnt->cnt_fast_fsync_fail +
				falsealm_cnt->cnt_sb_search_fail +
				falsealm_cnt->cnt_parity_fail +
				falsealm_cnt->cnt_rate_illegal +
				falsealm_cnt->cnt_crc8_fail +
				falsealm_cnt->cnt_mcs_fail +
				falsealm_cnt->cnt_cck_fail;

	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 1);
	/* update ofdm counter */
	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 0);
	/* update page C counter */
	rtl_set_bbreg(hw, ROFDM0_LSTF, BIT(31), 0);
	/* update page D counter */
	rtl_set_bbreg(hw, ROFDM1_LSTF, BIT(31), 0);
	if (rtlpriv->rtlhal.current_bandtype != BAND_ON_5G) {
		/* reset cck counter */
		rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
		rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 0);
		/* enable cck counter */
		rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 2);
		rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
	}
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "Cnt_Fast_Fsync_fail = %x, Cnt_SB_Search_fail = %x\n",
		 falsealm_cnt->cnt_fast_fsync_fail,
		 falsealm_cnt->cnt_sb_search_fail);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "Cnt_Parity_Fail = %x, Cnt_Rate_Illegal = %x, Cnt_Crc8_fail = %x, Cnt_Mcs_fail = %x\n",
		 falsealm_cnt->cnt_parity_fail,
		 falsealm_cnt->cnt_rate_illegal,
		 falsealm_cnt->cnt_crc8_fail,
		 falsealm_cnt->cnt_mcs_fail);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "Cnt_Ofdm_fail = %x, Cnt_Cck_fail = %x, Cnt_all = %x\n",
		 falsealm_cnt->cnt_ofdm_fail,
		 falsealm_cnt->cnt_cck_fail,
		 falsealm_cnt->cnt_all);
}