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
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ieee80211_chanctx_conf {int dummy; } ;
struct ath10k_vif {int is_started; int is_up; int /*<<< orphan*/  vdev_id; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,struct ieee80211_chanctx_conf*,int /*<<< orphan*/ ) ; 
 int ath10k_vdev_stop (struct ath10k_vif*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_vdev_down (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath10k_mac_op_unassign_vif_chanctx(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_chanctx_conf *ctx)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	int ret;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx unassign ptr %pK vdev_id %i\n",
		   ctx, arvif->vdev_id);

	WARN_ON(!arvif->is_started);

	if (vif->type == NL80211_IFTYPE_MONITOR) {
		WARN_ON(!arvif->is_up);

		ret = ath10k_wmi_vdev_down(ar, arvif->vdev_id);
		if (ret)
			ath10k_warn(ar, "failed to down monitor vdev %i: %d\n",
				    arvif->vdev_id, ret);

		arvif->is_up = false;
	}

	ret = ath10k_vdev_stop(arvif);
	if (ret)
		ath10k_warn(ar, "failed to stop vdev %i: %d\n",
			    arvif->vdev_id, ret);

	arvif->is_started = false;

	mutex_unlock(&ar->conf_mutex);
}