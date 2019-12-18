#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_2__ pubpi; TYPE_1__* sh; int /*<<< orphan*/  radio_chanspec; } ;
struct TYPE_3__ {scalar_t__ chip; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM47162 ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_2g_2057rev3 ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_2g_2057rev4n6 ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_2g_2057rev5 ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_2g_2057rev7 ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_5g ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_5g_2057 ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_5g_2057rev7 ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_rev5 ; 
 int /*<<< orphan*/ * nphy_tpc_txgain_ipa_rev6 ; 

__attribute__((used)) static u32 *wlc_phy_get_ipa_gaintbl_nphy(struct brcms_phy *pi)
{
	u32 *tx_pwrctrl_tbl = NULL;

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			if ((pi->pubpi.radiorev == 4)
			    || (pi->pubpi.radiorev == 6))
				tx_pwrctrl_tbl =
					nphy_tpc_txgain_ipa_2g_2057rev4n6;
			else if (pi->pubpi.radiorev == 3)
				tx_pwrctrl_tbl =
					nphy_tpc_txgain_ipa_2g_2057rev3;
			else if (pi->pubpi.radiorev == 5)
				tx_pwrctrl_tbl =
					nphy_tpc_txgain_ipa_2g_2057rev5;
			else if ((pi->pubpi.radiorev == 7)
				 || (pi->pubpi.radiorev == 8))
				tx_pwrctrl_tbl =
					nphy_tpc_txgain_ipa_2g_2057rev7;
		} else if (NREV_IS(pi->pubpi.phy_rev, 6)) {
			tx_pwrctrl_tbl = nphy_tpc_txgain_ipa_rev6;
			if (pi->sh->chip == BCMA_CHIP_ID_BCM47162)
				tx_pwrctrl_tbl = nphy_tpc_txgain_ipa_rev5;
		} else if (NREV_IS(pi->pubpi.phy_rev, 5)) {
			tx_pwrctrl_tbl = nphy_tpc_txgain_ipa_rev5;
		} else {
			tx_pwrctrl_tbl = nphy_tpc_txgain_ipa;
		}
	} else {

		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			if ((pi->pubpi.radiorev == 3) ||
			    (pi->pubpi.radiorev == 4) ||
			    (pi->pubpi.radiorev == 6))
				tx_pwrctrl_tbl = nphy_tpc_txgain_ipa_5g_2057;
			else if ((pi->pubpi.radiorev == 7)
				 || (pi->pubpi.radiorev == 8))
				tx_pwrctrl_tbl =
					nphy_tpc_txgain_ipa_5g_2057rev7;
		} else {
			tx_pwrctrl_tbl = nphy_tpc_txgain_ipa_5g;
		}
	}

	return tx_pwrctrl_tbl;
}