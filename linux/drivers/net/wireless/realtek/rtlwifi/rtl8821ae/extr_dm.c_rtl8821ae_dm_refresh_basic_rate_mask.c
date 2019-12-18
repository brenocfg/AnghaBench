#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct rtl_mac {scalar_t__ link_state; int basic_rates; } ;
struct dig_t {int rssi_val_min; } ;
struct rtl_priv {TYPE_2__* cfg; struct rtl_mac mac80211; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_BASIC_RATE ; 
 scalar_t__ MAC80211_LINKED ; 
 int RRSR_11M ; 
 int RRSR_1M ; 
 int RRSR_2M ; 
 int RRSR_5_5M ; 
 int RRSR_6M ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void rtl8821ae_dm_refresh_basic_rate_mask(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;
	struct rtl_mac *mac = &rtlpriv->mac80211;
	static u8 stage;
	u8 cur_stage = 0;
	u16 basic_rate = RRSR_1M | RRSR_2M | RRSR_5_5M | RRSR_11M | RRSR_6M;

	if (mac->link_state < MAC80211_LINKED)
		cur_stage = 0;
	else if (dm_digtable->rssi_val_min < 25)
		cur_stage = 1;
	else if (dm_digtable->rssi_val_min > 30)
		cur_stage = 3;
	else
		cur_stage = 2;

	if (cur_stage != stage) {
		if (cur_stage == 1) {
			basic_rate &= (!(basic_rate ^ mac->basic_rates));
			rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_BASIC_RATE, (u8 *)&basic_rate);
		} else if (cur_stage == 3 && (stage == 1 || stage == 2)) {
			rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_BASIC_RATE, (u8 *)&mac->basic_rates);
		}
	}
	stage = cur_stage;
}