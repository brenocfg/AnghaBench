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
struct ath_chanctx {int switch_after_beacon; scalar_t__ primary_sta; } ;
struct TYPE_2__ {struct ath_chanctx chan; } ;
struct ath_softc {int /*<<< orphan*/  nbcnvifs; struct ath_hw* sc_ah; TYPE_1__ offchannel; struct ath_chanctx* cur_chan; } ;
struct ath_hw {scalar_t__ opmode; scalar_t__ slottime; int /*<<< orphan*/  imask; } ;
struct ath_common {int /*<<< orphan*/  bssidmask; int /*<<< orphan*/  curbssid; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  op_flags; scalar_t__ curaid; } ;
struct ath9k_vif_iter_data {int naps; int beacons; scalar_t__ nmeshes; scalar_t__ nadhocs; scalar_t__ nstations; scalar_t__ primary_sta; scalar_t__ primary_beacon_vif; scalar_t__ slottime; int /*<<< orphan*/  nbcnvifs; scalar_t__ nwds; scalar_t__ nocbs; int /*<<< orphan*/  mask; int /*<<< orphan*/  hw_macaddr; scalar_t__ has_hw_macaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_INT_TSFOOR ; 
 int /*<<< orphan*/  ATH_OP_PRIM_STA_VIF ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 void* NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_OCB ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ath9k_beacon_config (struct ath_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  ath9k_beacon_ensure_primary_slot (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_calculate_iter_data (struct ath_softc*,struct ath_chanctx*,struct ath9k_vif_iter_data*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_global_settings (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_tsfadjust (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_setopmode (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_write_associd (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_mci_update_wlan_channels (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_set_assoc_state (struct ath_softc*,scalar_t__,int) ; 
 void ath9k_set_offchannel_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_chanctx_check_active (struct ath_softc*,struct ath_chanctx*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hw_setbssidmask (struct ath_common*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath9k_calculate_summary_state(struct ath_softc *sc,
				   struct ath_chanctx *ctx)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_vif_iter_data iter_data;

	ath_chanctx_check_active(sc, ctx);

	if (ctx != sc->cur_chan)
		return;

#ifdef CONFIG_ATH9K_CHANNEL_CONTEXT
	if (ctx == &sc->offchannel.chan)
		return ath9k_set_offchannel_state(sc);
#endif

	ath9k_ps_wakeup(sc);
	ath9k_calculate_iter_data(sc, ctx, &iter_data);

	if (iter_data.has_hw_macaddr)
		memcpy(common->macaddr, iter_data.hw_macaddr, ETH_ALEN);

	memcpy(common->bssidmask, iter_data.mask, ETH_ALEN);
	ath_hw_setbssidmask(common);

	if (iter_data.naps > 0) {
		ath9k_hw_set_tsfadjust(ah, true);
		ah->opmode = NL80211_IFTYPE_AP;
	} else {
		ath9k_hw_set_tsfadjust(ah, false);
		if (iter_data.beacons)
			ath9k_beacon_ensure_primary_slot(sc);

		if (iter_data.nmeshes)
			ah->opmode = NL80211_IFTYPE_MESH_POINT;
		else if (iter_data.nocbs)
			ah->opmode = NL80211_IFTYPE_OCB;
		else if (iter_data.nwds)
			ah->opmode = NL80211_IFTYPE_AP;
		else if (iter_data.nadhocs)
			ah->opmode = NL80211_IFTYPE_ADHOC;
		else
			ah->opmode = NL80211_IFTYPE_STATION;
	}

	ath9k_hw_setopmode(ah);

	ctx->switch_after_beacon = false;
	if ((iter_data.nstations + iter_data.nadhocs + iter_data.nmeshes) > 0)
		ah->imask |= ATH9K_INT_TSFOOR;
	else {
		ah->imask &= ~ATH9K_INT_TSFOOR;
		if (iter_data.naps == 1 && iter_data.beacons)
			ctx->switch_after_beacon = true;
	}

	if (ah->opmode == NL80211_IFTYPE_STATION) {
		bool changed = (iter_data.primary_sta != ctx->primary_sta);

		if (iter_data.primary_sta) {
			iter_data.primary_beacon_vif = iter_data.primary_sta;
			iter_data.beacons = true;
			ath9k_set_assoc_state(sc, iter_data.primary_sta,
					      changed);
			ctx->primary_sta = iter_data.primary_sta;
		} else {
			ctx->primary_sta = NULL;
			eth_zero_addr(common->curbssid);
			common->curaid = 0;
			ath9k_hw_write_associd(sc->sc_ah);
			if (ath9k_hw_mci_is_enabled(sc->sc_ah))
				ath9k_mci_update_wlan_channels(sc, true);
		}
	}
	sc->nbcnvifs = iter_data.nbcnvifs;
	ath9k_beacon_config(sc, iter_data.primary_beacon_vif,
			    iter_data.beacons);
	ath9k_hw_set_interrupts(ah);

	if (ah->slottime != iter_data.slottime) {
		ah->slottime = iter_data.slottime;
		ath9k_hw_init_global_settings(ah);
	}

	if (iter_data.primary_sta)
		set_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);
	else
		clear_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);

	ath_dbg(common, CONFIG,
		"macaddr: %pM, bssid: %pM, bssidmask: %pM\n",
		common->macaddr, common->curbssid, common->bssidmask);

	ath9k_ps_restore(sc);
}