#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  smps; } ;
struct iwl_priv {int /*<<< orphan*/  dynamic_frag_thresh; int /*<<< orphan*/  bt_duration; int /*<<< orphan*/  bt_on_thresh; int /*<<< orphan*/  bt_valid; int /*<<< orphan*/  kill_cts_mask; int /*<<< orphan*/  kill_ack_mask; TYPE_3__* lib; int /*<<< orphan*/ * contexts; int /*<<< orphan*/  rx_statistics_jiffies; scalar_t__ agg_tids_count; int /*<<< orphan*/  missed_beacon_threshold; TYPE_1__ current_ht_config; int /*<<< orphan*/  iw_mode; int /*<<< orphan*/  plcp_delta_threshold; int /*<<< orphan*/  band; int /*<<< orphan*/  calib_results; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sta_lock; } ;
struct TYPE_6__ {TYPE_2__* bt_params; int /*<<< orphan*/  plcp_delta_threshold; } ;
struct TYPE_5__ {scalar_t__ advanced_bt_coexist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DURATION_LIMIT_DEF ; 
 int /*<<< orphan*/  BT_FRAG_THRESHOLD_DEF ; 
 int /*<<< orphan*/  BT_ON_THRESHOLD_DEF ; 
 int /*<<< orphan*/  IEEE80211_SMPS_STATIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWLAGN_BT_ALL_VALID_MSK ; 
 int /*<<< orphan*/  IWLAGN_BT_KILL_ACK_MASK_DEFAULT ; 
 int /*<<< orphan*/  IWLAGN_BT_KILL_CTS_MASK_DEFAULT ; 
 int /*<<< orphan*/  IWL_MISSED_BEACON_THRESHOLD_DEF ; 
 size_t IWL_RXON_CTX_BSS ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  iwl_init_scan_params (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_set_rxon_chain (struct iwl_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_init_drv(struct iwl_priv *priv)
{
	spin_lock_init(&priv->sta_lock);

	mutex_init(&priv->mutex);

	INIT_LIST_HEAD(&priv->calib_results);

	priv->band = NL80211_BAND_2GHZ;

	priv->plcp_delta_threshold = priv->lib->plcp_delta_threshold;

	priv->iw_mode = NL80211_IFTYPE_STATION;
	priv->current_ht_config.smps = IEEE80211_SMPS_STATIC;
	priv->missed_beacon_threshold = IWL_MISSED_BEACON_THRESHOLD_DEF;
	priv->agg_tids_count = 0;

	priv->rx_statistics_jiffies = jiffies;

	/* Choose which receivers/antennas to use */
	iwlagn_set_rxon_chain(priv, &priv->contexts[IWL_RXON_CTX_BSS]);

	iwl_init_scan_params(priv);

	/* init bt coex */
	if (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) {
		priv->kill_ack_mask = IWLAGN_BT_KILL_ACK_MASK_DEFAULT;
		priv->kill_cts_mask = IWLAGN_BT_KILL_CTS_MASK_DEFAULT;
		priv->bt_valid = IWLAGN_BT_ALL_VALID_MSK;
		priv->bt_on_thresh = BT_ON_THRESHOLD_DEF;
		priv->bt_duration = BT_DURATION_LIMIT_DEF;
		priv->dynamic_frag_thresh = BT_FRAG_THRESHOLD_DEF;
	}

	return 0;
}