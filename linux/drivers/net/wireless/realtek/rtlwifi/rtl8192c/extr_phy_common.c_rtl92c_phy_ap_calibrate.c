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
struct rtl_phy {scalar_t__ apk_done; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 scalar_t__ IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl92c_phy_ap_calibrate (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92c_phy_ap_calibrate(struct ieee80211_hw *hw, s8 delta)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (rtlphy->apk_done)
		return;
	if (IS_92C_SERIAL(rtlhal->version))
		_rtl92c_phy_ap_calibrate(hw, delta, true);
	else
		_rtl92c_phy_ap_calibrate(hw, delta, false);
}