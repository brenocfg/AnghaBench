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
struct false_alarm_statistics {scalar_t__ cnt_all; } ;
struct dig_t {scalar_t__ fa_highthresh; int back_val; int backoffval_range_min; scalar_t__ fa_lowthresh; int backoffval_range_max; } ;
struct rtl_priv {struct false_alarm_statistics falsealm_cnt; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92s_backoff_enable_flag(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *digtable = &rtlpriv->dm_digtable;
	struct false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);

	if (falsealm_cnt->cnt_all > digtable->fa_highthresh) {
		if ((digtable->back_val - 6) <
			digtable->backoffval_range_min)
			digtable->back_val = digtable->backoffval_range_min;
		else
			digtable->back_val -= 6;
	} else if (falsealm_cnt->cnt_all < digtable->fa_lowthresh) {
		if ((digtable->back_val + 6) >
			digtable->backoffval_range_max)
			digtable->back_val =
				 digtable->backoffval_range_max;
		else
			digtable->back_val += 6;
	}
}