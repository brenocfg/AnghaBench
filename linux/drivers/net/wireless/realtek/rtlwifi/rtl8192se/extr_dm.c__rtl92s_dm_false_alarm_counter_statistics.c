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
struct false_alarm_statistics {int cnt_parity_fail; int cnt_rate_illegal; int cnt_crc8_fail; int cnt_mcs_fail; int cnt_ofdm_fail; int cnt_cck_fail; int cnt_all; } ;
struct rtl_priv {struct false_alarm_statistics falsealm_cnt; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 int ROFDM_PHYCOUNTER1 ; 
 int ROFDM_PHYCOUNTER2 ; 
 int ROFDM_PHYCOUNTER3 ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_dm_false_alarm_counter_statistics(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);
	u32 ret_value;

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER1, MASKDWORD);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER2, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER3, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);

	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
		falsealm_cnt->cnt_rate_illegal + falsealm_cnt->cnt_crc8_fail +
		falsealm_cnt->cnt_mcs_fail;

	/* read CCK false alarm */
	ret_value = rtl_get_bbreg(hw, 0xc64, MASKDWORD);
	falsealm_cnt->cnt_cck_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_all =	falsealm_cnt->cnt_ofdm_fail +
		falsealm_cnt->cnt_cck_fail;
}