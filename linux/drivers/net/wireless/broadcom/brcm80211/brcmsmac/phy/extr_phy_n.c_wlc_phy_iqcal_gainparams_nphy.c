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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct nphy_txgains {int* txlpf; int* txgm; int* pga; int* pad; int* ipa; } ;
struct nphy_iqcal_params {int txlpf; int txgm; int pga; int pad; int ipa; int cal_gain; int* ncorr; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 size_t NPHY_IQCAL_NUMGAINS ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 size_t*** tbl_iqcal_gainparams_nphy ; 

__attribute__((used)) static void
wlc_phy_iqcal_gainparams_nphy(struct brcms_phy *pi, u16 core_no,
			      struct nphy_txgains target_gain,
			      struct nphy_iqcal_params *params)
{
	u8 k;
	int idx;
	u16 gain_index;
	u8 band_idx = (CHSPEC_IS5G(pi->radio_chanspec) ? 1 : 0);

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		if (NREV_GE(pi->pubpi.phy_rev, 7))
			params->txlpf = target_gain.txlpf[core_no];

		params->txgm = target_gain.txgm[core_no];
		params->pga = target_gain.pga[core_no];
		params->pad = target_gain.pad[core_no];
		params->ipa = target_gain.ipa[core_no];
		if (NREV_GE(pi->pubpi.phy_rev, 7))
			params->cal_gain =
				((params->txlpf << 15) | (params->txgm << 12) |
				 (params->pga << 8) |
				 (params->pad << 3) | (params->ipa));
		else
			params->cal_gain =
				((params->txgm << 12) | (params->pga << 8) |
				 (params->pad << 4) | (params->ipa));

		params->ncorr[0] = 0x79;
		params->ncorr[1] = 0x79;
		params->ncorr[2] = 0x79;
		params->ncorr[3] = 0x79;
		params->ncorr[4] = 0x79;
	} else {

		gain_index = ((target_gain.pad[core_no] << 0) |
			      (target_gain.pga[core_no] << 4) |
			      (target_gain.txgm[core_no] << 8));

		idx = -1;
		for (k = 0; k < NPHY_IQCAL_NUMGAINS; k++) {
			if (tbl_iqcal_gainparams_nphy[band_idx][k][0] ==
			    gain_index) {
				idx = k;
				break;
			}
		}

		params->txgm = tbl_iqcal_gainparams_nphy[band_idx][k][1];
		params->pga = tbl_iqcal_gainparams_nphy[band_idx][k][2];
		params->pad = tbl_iqcal_gainparams_nphy[band_idx][k][3];
		params->cal_gain = ((params->txgm << 7) | (params->pga << 4) |
				    (params->pad << 2));
		params->ncorr[0] = tbl_iqcal_gainparams_nphy[band_idx][k][4];
		params->ncorr[1] = tbl_iqcal_gainparams_nphy[band_idx][k][5];
		params->ncorr[2] = tbl_iqcal_gainparams_nphy[band_idx][k][6];
		params->ncorr[3] = tbl_iqcal_gainparams_nphy[band_idx][k][7];
	}
}