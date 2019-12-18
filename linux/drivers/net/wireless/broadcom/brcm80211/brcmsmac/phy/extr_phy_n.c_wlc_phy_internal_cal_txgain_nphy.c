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
typedef  int u16 ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; int /*<<< orphan*/ * nphy_cal_orig_pwr_idx; int /*<<< orphan*/ * nphy_txcal_pwr_idx; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_TBL_ID_RFSEQ ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_index_nphy (struct brcms_phy*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wlc_phy_internal_cal_txgain_nphy(struct brcms_phy *pi)
{
	u16 txcal_gain[2];

	pi->nphy_txcal_pwr_idx[0] = pi->nphy_cal_orig_pwr_idx[0];
	pi->nphy_txcal_pwr_idx[1] = pi->nphy_cal_orig_pwr_idx[0];
	wlc_phy_txpwr_index_nphy(pi, 1, pi->nphy_cal_orig_pwr_idx[0], true);
	wlc_phy_txpwr_index_nphy(pi, 2, pi->nphy_cal_orig_pwr_idx[1], true);

	wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_RFSEQ, 2, 0x110, 16,
				txcal_gain);

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		txcal_gain[0] = (txcal_gain[0] & 0xF000) | 0x0F40;
		txcal_gain[1] = (txcal_gain[1] & 0xF000) | 0x0F40;
	} else {
		txcal_gain[0] = (txcal_gain[0] & 0xF000) | 0x0F60;
		txcal_gain[1] = (txcal_gain[1] & 0xF000) | 0x0F60;
	}

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ, 2, 0x110, 16,
				 txcal_gain);
}