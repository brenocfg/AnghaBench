#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  driver_flags; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_node {int no_ps_filter; struct ieee80211_vif* vif; int /*<<< orphan*/ * sta; struct ath_softc* sc; } ;
struct ath_vif {TYPE_1__* chanctx; int /*<<< orphan*/  list; struct ieee80211_vif* vif; struct ath_node mcast_node; } ;
struct ath_softc {int /*<<< orphan*/  mutex; TYPE_1__* cur_chan; struct ieee80211_vif* tx99_vif; struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;
struct TYPE_2__ {int nvifs; int /*<<< orphan*/  vifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  CONFIG_ATH9K_TX99 ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_VIF_GET_NOA_UPDATE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ath9k_assign_hw_queues (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_beacon_assign_slot (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_calculate_summary_state (struct ath_softc*,TYPE_1__*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_is_chanctx_enabled () ; 
 int /*<<< orphan*/  ath9k_set_txpower (struct ath_softc*,struct ieee80211_vif*) ; 
 scalar_t__ ath9k_uses_beacons (scalar_t__) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ath_tx_node_init (struct ath_softc*,struct ath_node*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_add_interface(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_vif *avp = (void *)vif->drv_priv;
	struct ath_node *an = &avp->mcast_node;

	mutex_lock(&sc->mutex);
	if (IS_ENABLED(CONFIG_ATH9K_TX99)) {
		if (sc->cur_chan->nvifs >= 1) {
			mutex_unlock(&sc->mutex);
			return -EOPNOTSUPP;
		}
		sc->tx99_vif = vif;
	}

	ath_dbg(common, CONFIG, "Attach a VIF of type: %d\n", vif->type);
	sc->cur_chan->nvifs++;

	if (vif->type == NL80211_IFTYPE_STATION && ath9k_is_chanctx_enabled())
		vif->driver_flags |= IEEE80211_VIF_GET_NOA_UPDATE;

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_assign_slot(sc, vif);

	avp->vif = vif;
	if (!ath9k_is_chanctx_enabled()) {
		avp->chanctx = sc->cur_chan;
		list_add_tail(&avp->list, &avp->chanctx->vifs);
	}

	ath9k_calculate_summary_state(sc, avp->chanctx);

	ath9k_assign_hw_queues(hw, vif);

	ath9k_set_txpower(sc, vif);

	an->sc = sc;
	an->sta = NULL;
	an->vif = vif;
	an->no_ps_filter = true;
	ath_tx_node_init(sc, an);

	mutex_unlock(&sc->mutex);
	return 0;
}