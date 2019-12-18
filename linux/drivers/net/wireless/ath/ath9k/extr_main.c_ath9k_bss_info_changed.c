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
typedef  int u32 ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  txpower_type; int /*<<< orphan*/  txpower; scalar_t__ use_short_slot; int /*<<< orphan*/  aid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  assoc; } ;
struct ath_vif {scalar_t__ chanctx; int /*<<< orphan*/  assoc; int /*<<< orphan*/  aid; int /*<<< orphan*/  bssid; } ;
struct TYPE_2__ {int slottime; int /*<<< orphan*/  updateslot; } ;
struct ath_softc {scalar_t__ cur_chan; int /*<<< orphan*/  mutex; TYPE_1__ beacon; struct ath_hw* sc_ah; } ;
struct ath_hw {int slottime; } ;
struct ath_common {int /*<<< orphan*/  curaid; int /*<<< orphan*/  curbssid; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INFO ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_IBSS ; 
 int BSS_CHANGED_OCB ; 
 int BSS_CHANGED_P2P_PS ; 
 int BSS_CHANGED_TXPOWER ; 
 int CHECK_ANI ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  UPDATE ; 
 int /*<<< orphan*/  ath9k_calculate_summary_state (struct ath_softc*,scalar_t__) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_global_settings (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_write_associd (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_p2p_bss_info_changed (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_set_txpower (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath_check_ani (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_bss_info_changed(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_bss_conf *bss_conf,
				   u32 changed)
{
#define CHECK_ANI				\
	(BSS_CHANGED_ASSOC |			\
	 BSS_CHANGED_IBSS |			\
	 BSS_CHANGED_BEACON_ENABLED)

	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_vif *avp = (void *)vif->drv_priv;
	int slottime;

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	if (changed & BSS_CHANGED_ASSOC) {
		ath_dbg(common, CONFIG, "BSSID %pM Changed ASSOC %d\n",
			bss_conf->bssid, bss_conf->assoc);

		memcpy(avp->bssid, bss_conf->bssid, ETH_ALEN);
		avp->aid = bss_conf->aid;
		avp->assoc = bss_conf->assoc;

		ath9k_calculate_summary_state(sc, avp->chanctx);
	}

	if ((changed & BSS_CHANGED_IBSS) ||
	      (changed & BSS_CHANGED_OCB)) {
		memcpy(common->curbssid, bss_conf->bssid, ETH_ALEN);
		common->curaid = bss_conf->aid;
		ath9k_hw_write_associd(sc->sc_ah);
	}

	if ((changed & BSS_CHANGED_BEACON_ENABLED) ||
	    (changed & BSS_CHANGED_BEACON_INT) ||
	    (changed & BSS_CHANGED_BEACON_INFO)) {
		ath9k_calculate_summary_state(sc, avp->chanctx);
	}

	if ((avp->chanctx == sc->cur_chan) &&
	    (changed & BSS_CHANGED_ERP_SLOT)) {
		if (bss_conf->use_short_slot)
			slottime = 9;
		else
			slottime = 20;

		if (vif->type == NL80211_IFTYPE_AP) {
			/*
			 * Defer update, so that connected stations can adjust
			 * their settings at the same time.
			 * See beacon.c for more details
			 */
			sc->beacon.slottime = slottime;
			sc->beacon.updateslot = UPDATE;
		} else {
			ah->slottime = slottime;
			ath9k_hw_init_global_settings(ah);
		}
	}

	if (changed & BSS_CHANGED_P2P_PS)
		ath9k_p2p_bss_info_changed(sc, vif);

	if (changed & CHECK_ANI)
		ath_check_ani(sc);

	if (changed & BSS_CHANGED_TXPOWER) {
		ath_dbg(common, CONFIG, "vif %pM power %d dbm power_type %d\n",
			vif->addr, bss_conf->txpower, bss_conf->txpower_type);
		ath9k_set_txpower(sc, vif);
	}

	mutex_unlock(&sc->mutex);
	ath9k_ps_restore(sc);

#undef CHECK_ANI
}