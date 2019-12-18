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
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_3__ def; } ;
struct ath10k_vif {int is_started; int is_up; int /*<<< orphan*/  vdev_id; } ;
struct TYPE_5__ {scalar_t__ tx_stats_over_pktlog; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  pktlog_filter; TYPE_2__ hw_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ATH10K_PKTLOG_PEER_STATS ; 
 int EBUSY ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,struct ieee80211_chanctx_conf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath10k_mac_can_set_cts_prot (struct ath10k_vif*) ; 
 int ath10k_mac_set_cts_prot (struct ath10k_vif*) ; 
 int ath10k_mac_vif_setup_ps (struct ath10k_vif*) ; 
 scalar_t__ ath10k_peer_stats_enabled (struct ath10k*) ; 
 int ath10k_vdev_start (struct ath10k_vif*,TYPE_3__*) ; 
 int /*<<< orphan*/  ath10k_vdev_stop (struct ath10k_vif*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int ath10k_wmi_pdev_pktlog_enable (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_vdev_up (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath10k_mac_op_assign_vif_chanctx(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_chanctx_conf *ctx)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	int ret;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx assign ptr %pK vdev_id %i\n",
		   ctx, arvif->vdev_id);

	if (WARN_ON(arvif->is_started)) {
		mutex_unlock(&ar->conf_mutex);
		return -EBUSY;
	}

	ret = ath10k_vdev_start(arvif, &ctx->def);
	if (ret) {
		ath10k_warn(ar, "failed to start vdev %i addr %pM on freq %d: %d\n",
			    arvif->vdev_id, vif->addr,
			    ctx->def.chan->center_freq, ret);
		goto err;
	}

	arvif->is_started = true;

	ret = ath10k_mac_vif_setup_ps(arvif);
	if (ret) {
		ath10k_warn(ar, "failed to update vdev %i ps: %d\n",
			    arvif->vdev_id, ret);
		goto err_stop;
	}

	if (vif->type == NL80211_IFTYPE_MONITOR) {
		ret = ath10k_wmi_vdev_up(ar, arvif->vdev_id, 0, vif->addr);
		if (ret) {
			ath10k_warn(ar, "failed to up monitor vdev %i: %d\n",
				    arvif->vdev_id, ret);
			goto err_stop;
		}

		arvif->is_up = true;
	}

	if (ath10k_mac_can_set_cts_prot(arvif)) {
		ret = ath10k_mac_set_cts_prot(arvif);
		if (ret)
			ath10k_warn(ar, "failed to set cts protection for vdev %d: %d\n",
				    arvif->vdev_id, ret);
	}

	if (ath10k_peer_stats_enabled(ar) &&
	    ar->hw_params.tx_stats_over_pktlog) {
		ar->pktlog_filter |= ATH10K_PKTLOG_PEER_STATS;
		ret = ath10k_wmi_pdev_pktlog_enable(ar,
						    ar->pktlog_filter);
		if (ret) {
			ath10k_warn(ar, "failed to enable pktlog %d\n", ret);
			goto err_stop;
		}
	}

	mutex_unlock(&ar->conf_mutex);
	return 0;

err_stop:
	ath10k_vdev_stop(arvif);
	arvif->is_started = false;
	ath10k_mac_vif_setup_ps(arvif);

err:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}