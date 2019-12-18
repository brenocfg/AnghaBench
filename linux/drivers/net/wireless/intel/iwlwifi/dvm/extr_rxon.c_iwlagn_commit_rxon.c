#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int filter_flags; int flags; scalar_t__ channel; int /*<<< orphan*/  bssid_addr; } ;
struct iwl_rxon_context {TYPE_4__ staging; int /*<<< orphan*/  ctxid; TYPE_3__* vif; int /*<<< orphan*/  is_active; int /*<<< orphan*/  active; } ;
struct iwl_rxon_cmd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_rts_for_aggregation; } ;
struct iwl_priv {scalar_t__ switch_channel; int /*<<< orphan*/  tx_power_next; int /*<<< orphan*/  status; TYPE_1__ hw_params; int /*<<< orphan*/  mutex; } ;
struct TYPE_10__ {int /*<<< orphan*/  swcrypto; } ;
struct TYPE_7__ {scalar_t__ use_short_slot; } ;
struct TYPE_8__ {TYPE_2__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IWL_DEBUG_11H (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
 int NUM_IWL_RXON_CTX ; 
 int RXON_FILTER_ASSOC_MSK ; 
 int RXON_FLG_BAND_24G_MSK ; 
 int RXON_FLG_SELF_CTS_EN ; 
 int RXON_FLG_SHORT_SLOT_MSK ; 
 int RXON_FLG_TSF2HOST_MSK ; 
 int /*<<< orphan*/  STATUS_CHANNEL_SWITCH_PENDING ; 
 int /*<<< orphan*/  iwl_calc_basic_rates (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int iwl_check_rxon_cmd (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  iwl_chswitch_done (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  iwl_full_rxon_required (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  iwl_is_alive (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_power_update_mode (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  iwl_print_rx_config_cmd (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_rxon_hwcrypto (struct iwl_priv*,struct iwl_rxon_context*,int) ; 
 int /*<<< orphan*/  iwl_set_tx_power (struct iwl_priv*,int /*<<< orphan*/ ,int) ; 
 int iwlagn_rxon_connect (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int iwlagn_rxon_disconn (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int iwlagn_send_rxon_assoc (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int iwlagn_set_pan_params (struct iwl_priv*) ; 
 TYPE_5__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct iwl_rxon_cmd*,TYPE_4__*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwlagn_commit_rxon(struct iwl_priv *priv, struct iwl_rxon_context *ctx)
{
	/* cast away the const for active_rxon in this function */
	struct iwl_rxon_cmd *active = (void *)&ctx->active;
	bool new_assoc = !!(ctx->staging.filter_flags & RXON_FILTER_ASSOC_MSK);
	int ret;

	lockdep_assert_held(&priv->mutex);

	if (!iwl_is_alive(priv))
		return -EBUSY;

	/* This function hardcodes a bunch of dual-mode assumptions */
	BUILD_BUG_ON(NUM_IWL_RXON_CTX != 2);

	if (!ctx->is_active)
		return 0;

	/* always get timestamp with Rx frame */
	ctx->staging.flags |= RXON_FLG_TSF2HOST_MSK;

	/* recalculate basic rates */
	iwl_calc_basic_rates(priv, ctx);

	/*
	 * force CTS-to-self frames protection if RTS-CTS is not preferred
	 * one aggregation protection method
	 */
	if (!priv->hw_params.use_rts_for_aggregation)
		ctx->staging.flags |= RXON_FLG_SELF_CTS_EN;

	if ((ctx->vif && ctx->vif->bss_conf.use_short_slot) ||
	    !(ctx->staging.flags & RXON_FLG_BAND_24G_MSK))
		ctx->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
	else
		ctx->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;

	iwl_print_rx_config_cmd(priv, ctx->ctxid);
	ret = iwl_check_rxon_cmd(priv, ctx);
	if (ret) {
		IWL_ERR(priv, "Invalid RXON configuration. Not committing.\n");
		return -EINVAL;
	}

	/*
	 * receive commit_rxon request
	 * abort any previous channel switch if still in process
	 */
	if (test_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status) &&
	    (priv->switch_channel != ctx->staging.channel)) {
		IWL_DEBUG_11H(priv, "abort channel switch on %d\n",
			      le16_to_cpu(priv->switch_channel));
		iwl_chswitch_done(priv, false);
	}

	/*
	 * If we don't need to send a full RXON, we can use
	 * iwl_rxon_assoc_cmd which is used to reconfigure filter
	 * and other flags for the current radio configuration.
	 */
	if (!iwl_full_rxon_required(priv, ctx)) {
		ret = iwlagn_send_rxon_assoc(priv, ctx);
		if (ret) {
			IWL_ERR(priv, "Error setting RXON_ASSOC (%d)\n", ret);
			return ret;
		}

		memcpy(active, &ctx->staging, sizeof(*active));
		/*
		 * We do not commit tx power settings while channel changing,
		 * do it now if after settings changed.
		 */
		iwl_set_tx_power(priv, priv->tx_power_next, false);

		/* make sure we are in the right PS state */
		iwl_power_update_mode(priv, true);

		return 0;
	}

	iwl_set_rxon_hwcrypto(priv, ctx, !iwlwifi_mod_params.swcrypto);

	IWL_DEBUG_INFO(priv,
		       "Going to commit RXON\n"
		       "  * with%s RXON_FILTER_ASSOC_MSK\n"
		       "  * channel = %d\n"
		       "  * bssid = %pM\n",
		       (new_assoc ? "" : "out"),
		       le16_to_cpu(ctx->staging.channel),
		       ctx->staging.bssid_addr);

	/*
	 * Always clear associated first, but with the correct config.
	 * This is required as for example station addition for the
	 * AP station must be done after the BSSID is set to correctly
	 * set up filters in the device.
	 */
	ret = iwlagn_rxon_disconn(priv, ctx);
	if (ret)
		return ret;

	ret = iwlagn_set_pan_params(priv);
	if (ret)
		return ret;

	if (new_assoc)
		return iwlagn_rxon_connect(priv, ctx);

	return 0;
}