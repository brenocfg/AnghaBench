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
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_dynack_node_deinit (int /*<<< orphan*/ ,struct ath_node*) ; 
 int /*<<< orphan*/  ath_tx_node_cleanup (struct ath_softc*,struct ath_node*) ; 

__attribute__((used)) static void ath_node_detach(struct ath_softc *sc, struct ieee80211_sta *sta)
{
	struct ath_node *an = (struct ath_node *)sta->drv_priv;
	ath_tx_node_cleanup(sc, an);

	ath_dynack_node_deinit(sc->sc_ah, an);
}