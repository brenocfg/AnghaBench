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
struct TYPE_2__ {int /*<<< orphan*/  dm_initialgain_enable; } ;
struct dig_t {int dig_enable_flag; } ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {TYPE_1__ dm; struct dig_t dm_digtable; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ RF_2T2R ; 
 int /*<<< orphan*/  _rtl92s_dm_ctrl_initgain_bytwoport (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_dm_ctrl_initgain_byrssi(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct dig_t *digtable = &rtlpriv->dm_digtable;

	/* 2T2R TP issue */
	if (rtlphy->rf_type == RF_2T2R)
		return;

	if (!rtlpriv->dm.dm_initialgain_enable)
		return;

	if (digtable->dig_enable_flag == false)
		return;

	_rtl92s_dm_ctrl_initgain_bytwoport(hw);
}