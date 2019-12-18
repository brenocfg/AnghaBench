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
struct ieee80211_vif_chanctx_switch {int dummy; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; } ;
typedef  enum ieee80211_chanctx_switch_mode { ____Placeholder_ieee80211_chanctx_switch_mode } ieee80211_chanctx_switch_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ath10k_mac_update_vif_chan (struct ath10k*,struct ieee80211_vif_chanctx_switch*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath10k_mac_op_switch_vif_chanctx(struct ieee80211_hw *hw,
				 struct ieee80211_vif_chanctx_switch *vifs,
				 int n_vifs,
				 enum ieee80211_chanctx_switch_mode mode)
{
	struct ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx switch n_vifs %d mode %d\n",
		   n_vifs, mode);
	ath10k_mac_update_vif_chan(ar, vifs, n_vifs);

	mutex_unlock(&ar->conf_mutex);
	return 0;
}