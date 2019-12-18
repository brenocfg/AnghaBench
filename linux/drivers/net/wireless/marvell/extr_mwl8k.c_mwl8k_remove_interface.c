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
struct mwl8k_vif {int dummy; } ;
struct mwl8k_priv {int dummy; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 struct mwl8k_vif* MWL8K_VIF (struct ieee80211_vif*) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  mwl8k_cmd_del_mac_addr (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_cmd_set_new_stn_del (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_remove_vif (struct mwl8k_priv*,struct mwl8k_vif*) ; 

__attribute__((used)) static void mwl8k_remove_interface(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_vif *mwl8k_vif = MWL8K_VIF(vif);

	if (vif->type == NL80211_IFTYPE_AP)
		mwl8k_cmd_set_new_stn_del(hw, vif, vif->addr);

	mwl8k_cmd_del_mac_addr(hw, vif, vif->addr);

	mwl8k_remove_vif(priv, mwl8k_vif);
}