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
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct ath_beacon_config {scalar_t__ enable_beacon; int /*<<< orphan*/  ibss_creator; int /*<<< orphan*/  intval; int /*<<< orphan*/  nexttbtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_BEACONS ; 
 int /*<<< orphan*/  ath9k_beacon_init (struct ath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_cmn_beacon_config_adhoc (struct ath_hw*,struct ath_beacon_config*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_reset_beacon_status (struct ath_softc*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_beacon_config_adhoc(struct ath_softc *sc,
				      struct ath_beacon_config *conf)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);

	ath9k_reset_beacon_status(sc);

	ath9k_cmn_beacon_config_adhoc(ah, conf);

	ath9k_beacon_init(sc, conf->nexttbtt, conf->intval);

	/*
	 * Set the global 'beacon has been configured' flag for the
	 * joiner case in IBSS mode.
	 */
	if (!conf->ibss_creator && conf->enable_beacon)
		set_bit(ATH_OP_BEACONS, &common->op_flags);
}