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
struct TYPE_2__ {int /*<<< orphan*/  iqk_lock; } ;
struct rtl_phy {int lck_inprogress; } ;
struct rtl_priv {TYPE_1__ locks; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8821ae_phy_iq_calibrate (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rtl8821ae_phy_iq_calibrate(struct ieee80211_hw *hw, bool b_recovery)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	if (!rtlphy->lck_inprogress) {
		spin_lock(&rtlpriv->locks.iqk_lock);
		rtlphy->lck_inprogress = true;
		spin_unlock(&rtlpriv->locks.iqk_lock);

		_rtl8821ae_phy_iq_calibrate(hw);

		spin_lock(&rtlpriv->locks.iqk_lock);
		rtlphy->lck_inprogress = false;
		spin_unlock(&rtlpriv->locks.iqk_lock);
	}
}