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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath9k_htc_sta {struct ath9k_htc_priv* htc_priv; int /*<<< orphan*/  rc_update_work; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ath9k_htc_add_station (struct ath9k_htc_priv*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ath9k_htc_init_rate (struct ath9k_htc_priv*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_sta_rc_update_work ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_htc_sta_add(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath9k_htc_sta *ista = (struct ath9k_htc_sta *) sta->drv_priv;
	int ret;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	ret = ath9k_htc_add_station(priv, vif, sta);
	if (!ret) {
		INIT_WORK(&ista->rc_update_work, ath9k_htc_sta_rc_update_work);
		ista->htc_priv = priv;
		ath9k_htc_init_rate(priv, sta);
	}
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	return ret;
}