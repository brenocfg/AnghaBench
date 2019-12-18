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
struct TYPE_2__ {int txpower_tracking; int txpower_trackinginit; int txpower_track_control; int* swing_idx_ofdm; int swing_idx_ofdm_cur; int swing_flag_ofdm; scalar_t__ txpowercount; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 size_t RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl88e_dm_init_txpower_tracking(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.txpower_tracking = true;
	rtlpriv->dm.txpower_trackinginit = false;
	rtlpriv->dm.txpowercount = 0;
	rtlpriv->dm.txpower_track_control = true;

	rtlpriv->dm.swing_idx_ofdm[RF90_PATH_A] = 12;
	rtlpriv->dm.swing_idx_ofdm_cur = 12;
	rtlpriv->dm.swing_flag_ofdm = false;
	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "rtlpriv->dm.txpower_tracking = %d\n",
		 rtlpriv->dm.txpower_tracking);
}