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
typedef  scalar_t__ u16 ;
struct TYPE_8__ {scalar_t__ flags; int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {int is_40mhz; int /*<<< orphan*/  extension_chan_offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel; } ;
struct iwl_rxon_context {int /*<<< orphan*/  vif; TYPE_3__ staging; TYPE_2__ ht; TYPE_1__ active; } ;
struct iwl_ht_config {int /*<<< orphan*/  smps; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; scalar_t__ switch_channel; int /*<<< orphan*/  status; TYPE_4__* lib; struct iwl_ht_config current_ht_config; struct iwl_rxon_context* contexts; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_conf {int /*<<< orphan*/  smps_mode; } ;
struct ieee80211_hw {struct ieee80211_conf conf; } ;
struct TYPE_10__ {struct ieee80211_channel* chan; } ;
struct ieee80211_channel_switch {TYPE_5__ chandef; } ;
struct ieee80211_channel {scalar_t__ hw_value; int /*<<< orphan*/  band; } ;
struct TYPE_9__ {scalar_t__ (* set_channel_switch ) (struct iwl_priv*,struct ieee80211_channel_switch*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_ABOVE ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_BELOW ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_NONE ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 size_t IWL_RXON_CTX_BSS ; 
#define  NL80211_CHAN_HT20 131 
#define  NL80211_CHAN_HT40MINUS 130 
#define  NL80211_CHAN_HT40PLUS 129 
#define  NL80211_CHAN_NO_HT 128 
 int /*<<< orphan*/  STATUS_CHANNEL_SWITCH_PENDING ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 
 int cfg80211_get_chandef_type (TYPE_5__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_is_associated_ctx (struct iwl_rxon_context*) ; 
 scalar_t__ iwl_is_rfkill (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_set_flags_for_band (struct iwl_priv*,struct iwl_rxon_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_rxon_channel (struct iwl_priv*,struct ieee80211_channel*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  iwl_set_rxon_ht (struct iwl_priv*,struct iwl_ht_config*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct iwl_priv*,struct ieee80211_channel_switch*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_mac_channel_switch(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_channel_switch *ch_switch)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct ieee80211_conf *conf = &hw->conf;
	struct ieee80211_channel *channel = ch_switch->chandef.chan;
	struct iwl_ht_config *ht_conf = &priv->current_ht_config;
	/*
	 * MULTI-FIXME
	 * When we add support for multiple interfaces, we need to
	 * revisit this. The channel switch command in the device
	 * only affects the BSS context, but what does that really
	 * mean? And what if we get a CSA on the second interface?
	 * This needs a lot of work.
	 */
	struct iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	u16 ch;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	mutex_lock(&priv->mutex);

	if (iwl_is_rfkill(priv))
		goto out;

	if (test_bit(STATUS_EXIT_PENDING, &priv->status) ||
	    test_bit(STATUS_SCANNING, &priv->status) ||
	    test_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status))
		goto out;

	if (!iwl_is_associated_ctx(ctx))
		goto out;

	if (!priv->lib->set_channel_switch)
		goto out;

	ch = channel->hw_value;
	if (le16_to_cpu(ctx->active.channel) == ch)
		goto out;

	priv->current_ht_config.smps = conf->smps_mode;

	/* Configure HT40 channels */
	switch (cfg80211_get_chandef_type(&ch_switch->chandef)) {
	case NL80211_CHAN_NO_HT:
	case NL80211_CHAN_HT20:
		ctx->ht.is_40mhz = false;
		ctx->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_NONE;
		break;
	case NL80211_CHAN_HT40MINUS:
		ctx->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		ctx->ht.is_40mhz = true;
		break;
	case NL80211_CHAN_HT40PLUS:
		ctx->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		ctx->ht.is_40mhz = true;
		break;
	}

	if ((le16_to_cpu(ctx->staging.channel) != ch))
		ctx->staging.flags = 0;

	iwl_set_rxon_channel(priv, channel, ctx);
	iwl_set_rxon_ht(priv, ht_conf);
	iwl_set_flags_for_band(priv, ctx, channel->band, ctx->vif);

	/*
	 * at this point, staging_rxon has the
	 * configuration for channel switch
	 */
	set_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status);
	priv->switch_channel = cpu_to_le16(ch);
	if (priv->lib->set_channel_switch(priv, ch_switch)) {
		clear_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status);
		priv->switch_channel = 0;
		ieee80211_chswitch_done(ctx->vif, false);
	}

out:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
}