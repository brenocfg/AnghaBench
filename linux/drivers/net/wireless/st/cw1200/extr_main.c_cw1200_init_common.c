#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_supported_band {int n_channels; TYPE_4__* channels; } ;
struct ieee80211_hw {int queues; int max_rates; int max_rate_tries; int sta_data_size; TYPE_3__* wiphy; scalar_t__ extra_tx_headroom; struct cw1200_common* priv; } ;
struct cw1200_sta_priv {int dummy; } ;
struct TYPE_6__ {int done; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  probe_work; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct cw1200_common {int hw_type; int ba_rx_tid_mask; int ba_tx_tid_mask; int rts_threshold; TYPE_2__ wsm_cmd; int /*<<< orphan*/  wsm_cmd_buf; int /*<<< orphan*/  ps_mode_switch_done; int /*<<< orphan*/  wsm_startup_done; int /*<<< orphan*/  wsm_cmd_wq; int /*<<< orphan*/  channel_switch_done; int /*<<< orphan*/  tx_queue_stats; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  mcast_timeout; int /*<<< orphan*/  set_beacon_wakeup_period_work; int /*<<< orphan*/  update_filtering_work; int /*<<< orphan*/  linkid_reset_work; int /*<<< orphan*/  link_id_gc_work; int /*<<< orphan*/  link_id_work; int /*<<< orphan*/  multicast_stop_work; int /*<<< orphan*/  multicast_start_work; int /*<<< orphan*/  set_tim_work; int /*<<< orphan*/  set_cts_work; int /*<<< orphan*/  ps_state_lock; int /*<<< orphan*/  bss_loss_lock; int /*<<< orphan*/  bss_params_work; int /*<<< orphan*/  bss_loss_work; int /*<<< orphan*/  event_handler; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  event_queue_lock; int /*<<< orphan*/  tx_policy_upload_work; int /*<<< orphan*/  wep_key_work; int /*<<< orphan*/  join_complete_work; int /*<<< orphan*/  unjoin_work; int /*<<< orphan*/  join_timeout; int /*<<< orphan*/  clear_recent_scan_work; TYPE_1__ scan; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  wsm_cmd_mux; int /*<<< orphan*/  mcs_rates; int /*<<< orphan*/  rates; int /*<<< orphan*/  mode; struct ieee80211_hw* hw; } ;
struct TYPE_8__ {int max_power; scalar_t__ max_antenna_gain; scalar_t__ flags; } ;
struct TYPE_7__ {int interface_modes; int max_scan_ssids; scalar_t__* perm_addr; int /*<<< orphan*/  max_scan_ie_len; struct ieee80211_supported_band** bands; int /*<<< orphan*/  flags; int /*<<< orphan*/ * wowlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTION_MONITOR ; 
 int /*<<< orphan*/  CW1200_LINK_ID_MAX ; 
 int /*<<< orphan*/  IEEE80211_MAX_DATA_LEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEED_DTIM_BEFORE_ASSOC ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_CLIENT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SUPPORTS_DYNAMIC_PS ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int /*<<< orphan*/  TX_AMPDU_SETUP_IN_HW ; 
 int /*<<< orphan*/  WIPHY_FLAG_AP_UAPSD ; 
 scalar_t__ WSM_TX_EXTRA_HEADROOM ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int cw1200_ba_rx_tids ; 
 int cw1200_ba_tx_tids ; 
 struct ieee80211_supported_band cw1200_band_2ghz ; 
 struct ieee80211_supported_band cw1200_band_5ghz ; 
 int /*<<< orphan*/  cw1200_bss_loss_work ; 
 int /*<<< orphan*/  cw1200_bss_params_work ; 
 int /*<<< orphan*/  cw1200_clear_recent_scan_work ; 
 int /*<<< orphan*/  cw1200_event_handler ; 
 int /*<<< orphan*/  cw1200_join_complete_work ; 
 int /*<<< orphan*/  cw1200_join_timeout ; 
 int /*<<< orphan*/  cw1200_link_id_gc_work ; 
 int /*<<< orphan*/  cw1200_link_id_reset ; 
 int /*<<< orphan*/  cw1200_link_id_work ; 
 int /*<<< orphan*/ * cw1200_mac_template ; 
 int /*<<< orphan*/  cw1200_mcast_timeout ; 
 int /*<<< orphan*/  cw1200_multicast_start_work ; 
 int /*<<< orphan*/  cw1200_multicast_stop_work ; 
 int /*<<< orphan*/  cw1200_n_rates ; 
 int /*<<< orphan*/  cw1200_ops ; 
 int /*<<< orphan*/  cw1200_probe_work ; 
 int /*<<< orphan*/  cw1200_queue_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ cw1200_queue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_queue_stats_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ cw1200_queue_stats_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_rates ; 
 int /*<<< orphan*/  cw1200_scan_timeout ; 
 int /*<<< orphan*/  cw1200_scan_work ; 
 int /*<<< orphan*/  cw1200_set_beacon_wakeup_period_work ; 
 int /*<<< orphan*/  cw1200_set_cts_work ; 
 int /*<<< orphan*/  cw1200_set_tim_work ; 
 int /*<<< orphan*/  cw1200_skb_dtor ; 
 int /*<<< orphan*/ * cw1200_ttl ; 
 int /*<<< orphan*/  cw1200_unjoin_work ; 
 int /*<<< orphan*/  cw1200_update_filtering_work ; 
 int /*<<< orphan*/  cw1200_wep_key_work ; 
 int /*<<< orphan*/  cw1200_wowlan_support ; 
 int /*<<< orphan*/  get_random_bytes (scalar_t__*,int) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_policy_init (struct cw1200_common*) ; 
 int /*<<< orphan*/  tx_policy_upload_work ; 
 int /*<<< orphan*/  wsm_buf_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ieee80211_hw *cw1200_init_common(const u8 *macaddr,
						const bool have_5ghz)
{
	int i, band;
	struct ieee80211_hw *hw;
	struct cw1200_common *priv;

	hw = ieee80211_alloc_hw(sizeof(struct cw1200_common), &cw1200_ops);
	if (!hw)
		return NULL;

	priv = hw->priv;
	priv->hw = hw;
	priv->hw_type = -1;
	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->rates = cw1200_rates; /* TODO: fetch from FW */
	priv->mcs_rates = cw1200_n_rates;
	if (cw1200_ba_rx_tids != -1)
		priv->ba_rx_tid_mask = cw1200_ba_rx_tids;
	else
		priv->ba_rx_tid_mask = 0xFF; /* Enable RX BLKACK for all TIDs */
	if (cw1200_ba_tx_tids != -1)
		priv->ba_tx_tid_mask = cw1200_ba_tx_tids;
	else
		priv->ba_tx_tid_mask = 0xff; /* Enable TX BLKACK for all TIDs */

	ieee80211_hw_set(hw, NEED_DTIM_BEFORE_ASSOC);
	ieee80211_hw_set(hw, TX_AMPDU_SETUP_IN_HW);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, CONNECTION_MONITOR);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, SUPPORTS_PS);

	hw->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
					  BIT(NL80211_IFTYPE_ADHOC) |
					  BIT(NL80211_IFTYPE_AP) |
					  BIT(NL80211_IFTYPE_MESH_POINT) |
					  BIT(NL80211_IFTYPE_P2P_CLIENT) |
					  BIT(NL80211_IFTYPE_P2P_GO);

#ifdef CONFIG_PM
	hw->wiphy->wowlan = &cw1200_wowlan_support;
#endif

	hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;

	hw->queues = 4;

	priv->rts_threshold = -1;

	hw->max_rates = 8;
	hw->max_rate_tries = 15;
	hw->extra_tx_headroom = WSM_TX_EXTRA_HEADROOM +
		8;  /* TKIP IV */

	hw->sta_data_size = sizeof(struct cw1200_sta_priv);

	hw->wiphy->bands[NL80211_BAND_2GHZ] = &cw1200_band_2ghz;
	if (have_5ghz)
		hw->wiphy->bands[NL80211_BAND_5GHZ] = &cw1200_band_5ghz;

	/* Channel params have to be cleared before registering wiphy again */
	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		struct ieee80211_supported_band *sband = hw->wiphy->bands[band];
		if (!sband)
			continue;
		for (i = 0; i < sband->n_channels; i++) {
			sband->channels[i].flags = 0;
			sband->channels[i].max_antenna_gain = 0;
			sband->channels[i].max_power = 30;
		}
	}

	hw->wiphy->max_scan_ssids = 2;
	hw->wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;

	if (macaddr)
		SET_IEEE80211_PERM_ADDR(hw, (u8 *)macaddr);
	else
		SET_IEEE80211_PERM_ADDR(hw, cw1200_mac_template);

	/* Fix up mac address if necessary */
	if (hw->wiphy->perm_addr[3] == 0 &&
	    hw->wiphy->perm_addr[4] == 0 &&
	    hw->wiphy->perm_addr[5] == 0) {
		get_random_bytes(&hw->wiphy->perm_addr[3], 3);
	}

	mutex_init(&priv->wsm_cmd_mux);
	mutex_init(&priv->conf_mutex);
	priv->workqueue = create_singlethread_workqueue("cw1200_wq");
	if (!priv->workqueue) {
		ieee80211_free_hw(hw);
		return NULL;
	}

	sema_init(&priv->scan.lock, 1);
	INIT_WORK(&priv->scan.work, cw1200_scan_work);
	INIT_DELAYED_WORK(&priv->scan.probe_work, cw1200_probe_work);
	INIT_DELAYED_WORK(&priv->scan.timeout, cw1200_scan_timeout);
	INIT_DELAYED_WORK(&priv->clear_recent_scan_work,
			  cw1200_clear_recent_scan_work);
	INIT_DELAYED_WORK(&priv->join_timeout, cw1200_join_timeout);
	INIT_WORK(&priv->unjoin_work, cw1200_unjoin_work);
	INIT_WORK(&priv->join_complete_work, cw1200_join_complete_work);
	INIT_WORK(&priv->wep_key_work, cw1200_wep_key_work);
	INIT_WORK(&priv->tx_policy_upload_work, tx_policy_upload_work);
	spin_lock_init(&priv->event_queue_lock);
	INIT_LIST_HEAD(&priv->event_queue);
	INIT_WORK(&priv->event_handler, cw1200_event_handler);
	INIT_DELAYED_WORK(&priv->bss_loss_work, cw1200_bss_loss_work);
	INIT_WORK(&priv->bss_params_work, cw1200_bss_params_work);
	spin_lock_init(&priv->bss_loss_lock);
	spin_lock_init(&priv->ps_state_lock);
	INIT_WORK(&priv->set_cts_work, cw1200_set_cts_work);
	INIT_WORK(&priv->set_tim_work, cw1200_set_tim_work);
	INIT_WORK(&priv->multicast_start_work, cw1200_multicast_start_work);
	INIT_WORK(&priv->multicast_stop_work, cw1200_multicast_stop_work);
	INIT_WORK(&priv->link_id_work, cw1200_link_id_work);
	INIT_DELAYED_WORK(&priv->link_id_gc_work, cw1200_link_id_gc_work);
	INIT_WORK(&priv->linkid_reset_work, cw1200_link_id_reset);
	INIT_WORK(&priv->update_filtering_work, cw1200_update_filtering_work);
	INIT_WORK(&priv->set_beacon_wakeup_period_work,
		  cw1200_set_beacon_wakeup_period_work);
	timer_setup(&priv->mcast_timeout, cw1200_mcast_timeout, 0);

	if (cw1200_queue_stats_init(&priv->tx_queue_stats,
				    CW1200_LINK_ID_MAX,
				    cw1200_skb_dtor,
				    priv)) {
		ieee80211_free_hw(hw);
		return NULL;
	}

	for (i = 0; i < 4; ++i) {
		if (cw1200_queue_init(&priv->tx_queue[i],
				      &priv->tx_queue_stats, i, 16,
				      cw1200_ttl[i])) {
			for (; i > 0; i--)
				cw1200_queue_deinit(&priv->tx_queue[i - 1]);
			cw1200_queue_stats_deinit(&priv->tx_queue_stats);
			ieee80211_free_hw(hw);
			return NULL;
		}
	}

	init_waitqueue_head(&priv->channel_switch_done);
	init_waitqueue_head(&priv->wsm_cmd_wq);
	init_waitqueue_head(&priv->wsm_startup_done);
	init_waitqueue_head(&priv->ps_mode_switch_done);
	wsm_buf_init(&priv->wsm_cmd_buf);
	spin_lock_init(&priv->wsm_cmd.lock);
	priv->wsm_cmd.done = 1;
	tx_policy_init(priv);

	return hw;
}