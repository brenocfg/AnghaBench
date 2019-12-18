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
struct TYPE_2__ {scalar_t__ defant; int rxotherant; } ;
struct ath_softc {TYPE_1__ rx; struct ath_hw* sc_ah; } ;
struct ath_rx_status {scalar_t__ rs_antenna; } ;
struct ath9k_hw_capabilities {int hw_caps; } ;
struct ath_hw {struct ath9k_hw_capabilities caps; } ;
struct ath_common {scalar_t__ bt_ant_diversity; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_ANT_DIV_COMB ; 
 int ATH9K_HW_CAP_BT_ANT_DIV ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_ant_comb_scan (struct ath_softc*,struct ath_rx_status*) ; 
 int /*<<< orphan*/  ath_setdefantenna (struct ath_softc*,scalar_t__) ; 

__attribute__((used)) static void ath9k_antenna_check(struct ath_softc *sc,
				struct ath_rx_status *rs)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath9k_hw_capabilities *pCap = &ah->caps;
	struct ath_common *common = ath9k_hw_common(ah);

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB))
		return;

	/*
	 * Change the default rx antenna if rx diversity
	 * chooses the other antenna 3 times in a row.
	 */
	if (sc->rx.defant != rs->rs_antenna) {
		if (++sc->rx.rxotherant >= 3)
			ath_setdefantenna(sc, rs->rs_antenna);
	} else {
		sc->rx.rxotherant = 0;
	}

	if (pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV) {
		if (common->bt_ant_diversity)
			ath_ant_comb_scan(sc, rs);
	} else {
		ath_ant_comb_scan(sc, rs);
	}
}