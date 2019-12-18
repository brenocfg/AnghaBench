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
struct iwl_rxon_context {struct ieee80211_vif* vif; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct iwl_rxon_context* iwl_rxon_ctx_from_vif (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_teardown_interface (struct iwl_priv*,struct ieee80211_vif*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_mac_remove_interface(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct iwl_rxon_context *ctx = iwl_rxon_ctx_from_vif(vif);

	IWL_DEBUG_MAC80211(priv, "enter\n");

	mutex_lock(&priv->mutex);

	WARN_ON(ctx->vif != vif);
	ctx->vif = NULL;

	iwl_teardown_interface(priv, vif, false);

	mutex_unlock(&priv->mutex);

	IWL_DEBUG_MAC80211(priv, "leave\n");

}