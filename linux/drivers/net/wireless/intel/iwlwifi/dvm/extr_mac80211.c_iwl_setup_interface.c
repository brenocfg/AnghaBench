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
struct iwl_rxon_context {int is_active; int /*<<< orphan*/  mcast_queue; int /*<<< orphan*/ * ac_to_queue; int /*<<< orphan*/  always_active; struct ieee80211_vif* vif; } ;
struct iwl_priv {scalar_t__ iw_mode; int /*<<< orphan*/  bt_traffic_load; TYPE_2__* lib; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  cab_queue; int /*<<< orphan*/ * hw_queue; } ;
struct TYPE_4__ {TYPE_1__* bt_params; } ;
struct TYPE_3__ {scalar_t__ advanced_bt_coexist; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_INVAL_HW_QUEUE ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  IWL_BT_COEX_TRAFFIC_LOAD_HIGH ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int iwl_set_mode (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_setup_interface(struct iwl_priv *priv,
			       struct iwl_rxon_context *ctx)
{
	struct ieee80211_vif *vif = ctx->vif;
	int err, ac;

	lockdep_assert_held(&priv->mutex);

	/*
	 * This variable will be correct only when there's just
	 * a single context, but all code using it is for hardware
	 * that supports only one context.
	 */
	priv->iw_mode = vif->type;

	ctx->is_active = true;

	err = iwl_set_mode(priv, ctx);
	if (err) {
		if (!ctx->always_active)
			ctx->is_active = false;
		return err;
	}

	if (priv->lib->bt_params && priv->lib->bt_params->advanced_bt_coexist &&
	    vif->type == NL80211_IFTYPE_ADHOC) {
		/*
		 * pretend to have high BT traffic as long as we
		 * are operating in IBSS mode, as this will cause
		 * the rate scaling etc. to behave as intended.
		 */
		priv->bt_traffic_load = IWL_BT_COEX_TRAFFIC_LOAD_HIGH;
	}

	/* set up queue mappings */
	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		vif->hw_queue[ac] = ctx->ac_to_queue[ac];

	if (vif->type == NL80211_IFTYPE_AP)
		vif->cab_queue = ctx->mcast_queue;
	else
		vif->cab_queue = IEEE80211_INVAL_HW_QUEUE;

	return 0;
}