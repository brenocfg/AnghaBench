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
struct TYPE_2__ {scalar_t__ cnt_all; } ;
struct dig_t {scalar_t__ fa_highthresh; int back_val; int back_range_min; scalar_t__ fa_lowthresh; int back_range_max; int rssi_val_min; int rx_gain_max; int cur_igvalue; int rx_gain_min; } ;
struct rtl_priv {TYPE_1__ falsealm_cnt; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_write_dig (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92c_dm_ctrl_initgain_by_rssi(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	if (rtlpriv->falsealm_cnt.cnt_all > dm_digtable->fa_highthresh) {
		if ((dm_digtable->back_val - 2) <
		    dm_digtable->back_range_min)
			dm_digtable->back_val =
			    dm_digtable->back_range_min;
		else
			dm_digtable->back_val -= 2;
	} else if (rtlpriv->falsealm_cnt.cnt_all < dm_digtable->fa_lowthresh) {
		if ((dm_digtable->back_val + 2) >
		    dm_digtable->back_range_max)
			dm_digtable->back_val =
			    dm_digtable->back_range_max;
		else
			dm_digtable->back_val += 2;
	}

	if ((dm_digtable->rssi_val_min + 10 - dm_digtable->back_val) >
	    dm_digtable->rx_gain_max)
		dm_digtable->cur_igvalue = dm_digtable->rx_gain_max;
	else if ((dm_digtable->rssi_val_min + 10 -
		  dm_digtable->back_val) < dm_digtable->rx_gain_min)
		dm_digtable->cur_igvalue = dm_digtable->rx_gain_min;
	else
		dm_digtable->cur_igvalue = dm_digtable->rssi_val_min + 10 -
		    dm_digtable->back_val;

	RT_TRACE(rtlpriv, COMP_DIG, DBG_TRACE,
		 "rssi_val_min = %x back_val %x\n",
		  dm_digtable->rssi_val_min, dm_digtable->back_val);

	rtl8723e_dm_write_dig(hw);
}