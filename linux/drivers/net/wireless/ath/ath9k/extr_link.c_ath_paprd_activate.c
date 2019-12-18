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
struct ath_hw {int txchainmask; struct ath9k_hw_cal_data* caldata; } ;
struct ath_common {int dummy; } ;
struct ath9k_hw_cal_data {int /*<<< orphan*/  cal_flags; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int BIT (int) ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int /*<<< orphan*/  PAPRD_DONE ; 
 int /*<<< orphan*/  ar9003_paprd_enable (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_paprd_populate_single_table (struct ath_hw*,struct ath9k_hw_cal_data*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath_paprd_activate(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_cal_data *caldata = ah->caldata;
	int chain;

	if (!caldata || !test_bit(PAPRD_DONE, &caldata->cal_flags)) {
		ath_dbg(common, CALIBRATE, "Failed to activate PAPRD\n");
		return;
	}

	ar9003_paprd_enable(ah, false);
	for (chain = 0; chain < AR9300_MAX_CHAINS; chain++) {
		if (!(ah->txchainmask & BIT(chain)))
			continue;

		ar9003_paprd_populate_single_table(ah, caldata, chain);
	}

	ath_dbg(common, CALIBRATE, "Activating PAPRD\n");
	ar9003_paprd_enable(ah, true);
}