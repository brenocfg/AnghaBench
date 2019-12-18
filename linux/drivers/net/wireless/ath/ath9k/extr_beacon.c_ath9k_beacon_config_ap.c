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
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;
struct ath_beacon_config {int /*<<< orphan*/  intval; int /*<<< orphan*/  nexttbtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_BCBUF ; 
 int /*<<< orphan*/  ath9k_beacon_init (struct ath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_cmn_beacon_config_ap (struct ath_hw*,struct ath_beacon_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_beacon_config_ap(struct ath_softc *sc,
				   struct ath_beacon_config *conf)
{
	struct ath_hw *ah = sc->sc_ah;

	ath9k_cmn_beacon_config_ap(ah, conf, ATH_BCBUF);
	ath9k_beacon_init(sc, conf->nexttbtt, conf->intval);
}