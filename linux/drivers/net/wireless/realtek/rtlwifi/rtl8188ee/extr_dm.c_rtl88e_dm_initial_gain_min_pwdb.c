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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {long entry_min_undec_sm_pwdb; long undec_sm_pwdb; } ;
struct dig_t {scalar_t__ curmultista_cstate; scalar_t__ cur_sta_cstate; } ;
struct rtl_priv {TYPE_1__ dm; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIG_MULTISTA_CONNECT ; 
 scalar_t__ DIG_STA_BEFORE_CONNECT ; 
 scalar_t__ DIG_STA_CONNECT ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 rtl88e_dm_initial_gain_min_pwdb(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_dig = &rtlpriv->dm_digtable;
	long rssi_val_min = 0;

	if ((dm_dig->curmultista_cstate == DIG_MULTISTA_CONNECT) &&
	    (dm_dig->cur_sta_cstate == DIG_STA_CONNECT)) {
		if (rtlpriv->dm.entry_min_undec_sm_pwdb != 0)
			rssi_val_min =
			    (rtlpriv->dm.entry_min_undec_sm_pwdb >
			     rtlpriv->dm.undec_sm_pwdb) ?
			    rtlpriv->dm.undec_sm_pwdb :
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
		else
			rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
	} else if (dm_dig->cur_sta_cstate == DIG_STA_CONNECT ||
		   dm_dig->cur_sta_cstate == DIG_STA_BEFORE_CONNECT) {
		rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
	} else if (dm_dig->curmultista_cstate ==
		DIG_MULTISTA_CONNECT) {
		rssi_val_min = rtlpriv->dm.entry_min_undec_sm_pwdb;
	}

	return (u8)rssi_val_min;
}