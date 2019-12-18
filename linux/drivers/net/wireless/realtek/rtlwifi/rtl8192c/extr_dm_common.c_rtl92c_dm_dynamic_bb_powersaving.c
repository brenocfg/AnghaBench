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
struct TYPE_2__ {scalar_t__ entry_min_undec_sm_pwdb; scalar_t__ undec_sm_pwdb; } ;
struct ps_t {scalar_t__ rssi_val_min; } ;
struct rtl_priv {TYPE_1__ dm; struct ps_t dm_pstable; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ opmode; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ MAC80211_NOLINK ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtl92c_dm_rf_saving (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92c_dm_dynamic_bb_powersaving(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct ps_t *dm_pstable = &rtlpriv->dm_pstable;
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	/* Determine the minimum RSSI */
	if (((mac->link_state == MAC80211_NOLINK)) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) {
		dm_pstable->rssi_val_min = 0;
		RT_TRACE(rtlpriv, DBG_LOUD, DBG_LOUD, "Not connected to any\n");
	}

	if (mac->link_state == MAC80211_LINKED) {
		if (mac->opmode == NL80211_IFTYPE_ADHOC) {
			dm_pstable->rssi_val_min =
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
			RT_TRACE(rtlpriv, DBG_LOUD, DBG_LOUD,
				 "AP Client PWDB = 0x%lx\n",
				 dm_pstable->rssi_val_min);
		} else {
			dm_pstable->rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
			RT_TRACE(rtlpriv, DBG_LOUD, DBG_LOUD,
				 "STA Default Port PWDB = 0x%lx\n",
				 dm_pstable->rssi_val_min);
		}
	} else {
		dm_pstable->rssi_val_min =
		    rtlpriv->dm.entry_min_undec_sm_pwdb;

		RT_TRACE(rtlpriv, DBG_LOUD, DBG_LOUD,
			 "AP Ext Port PWDB = 0x%lx\n",
			 dm_pstable->rssi_val_min);
	}

	/* Power Saving for 92C */
	if (IS_92C_SERIAL(rtlhal->version))
		;/* rtl92c_dm_1r_cca(hw); */
	else
		rtl92c_dm_rf_saving(hw, false);
}