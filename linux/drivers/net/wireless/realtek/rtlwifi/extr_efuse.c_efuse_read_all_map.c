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
struct rtl_priv {TYPE_1__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * maps; } ;

/* Variables and functions */
 size_t EFUSE_HWSET_MAX_SIZE ; 
 int /*<<< orphan*/  efuse_power_switch (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  read_efuse (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void efuse_read_all_map(struct ieee80211_hw *hw, u8 *efuse)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	efuse_power_switch(hw, false, true);
	read_efuse(hw, 0, rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE], efuse);
	efuse_power_switch(hw, false, false);
}