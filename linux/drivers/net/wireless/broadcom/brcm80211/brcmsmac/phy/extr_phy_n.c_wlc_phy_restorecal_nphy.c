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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxcal_coeffs_5G; scalar_t__* txcal_radio_regs_5G; int /*<<< orphan*/  rxcal_coeffs_2G; scalar_t__* txcal_radio_regs_2G; scalar_t__* txcal_coeffs_5G; scalar_t__* txcal_coeffs_2G; } ;
struct brcms_phy {scalar_t__ nphy_iqcal_chanspec_2G; scalar_t__ nphy_iqcal_chanspec_5G; TYPE_1__ pubpi; TYPE_2__ calibration_cache; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOFT_COARSE_I ; 
 int /*<<< orphan*/  LOFT_COARSE_Q ; 
 int /*<<< orphan*/  LOFT_FINE_I ; 
 int /*<<< orphan*/  LOFT_FINE_Q ; 
 int /*<<< orphan*/  NPHY_TBL_ID_IQLOCAL ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int RADIO_2055_CORE1_TX_BB_MXGM ; 
 int RADIO_2055_CORE1_TX_VOS_CNCL ; 
 int RADIO_2055_CORE2_TX_BB_MXGM ; 
 int RADIO_2055_CORE2_TX_VOS_CNCL ; 
 int RADIO_2056_TX0 ; 
 int RADIO_2056_TX1 ; 
 int RADIO_2056_TX_LOFT_COARSE_I ; 
 int RADIO_2056_TX_LOFT_COARSE_Q ; 
 int RADIO_2056_TX_LOFT_FINE_I ; 
 int RADIO_2056_TX_LOFT_FINE_Q ; 
 int /*<<< orphan*/  RADIO_2057 ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  WRITE_RADIO_REG3 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wlc_phy_rx_iq_coeffs_nphy (struct brcms_phy*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  wlc_phy_tx_iq_war_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,scalar_t__) ; 

__attribute__((used)) static void wlc_phy_restorecal_nphy(struct brcms_phy *pi)
{
	u16 *loft_comp;
	u16 txcal_coeffs_bphy[4];
	u16 *tbl_ptr;
	int coreNum;
	u16 *txcal_radio_regs = NULL;

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if (pi->nphy_iqcal_chanspec_2G == 0)
			return;

		tbl_ptr = pi->calibration_cache.txcal_coeffs_2G;
		loft_comp = &pi->calibration_cache.txcal_coeffs_2G[5];
	} else {
		if (pi->nphy_iqcal_chanspec_5G == 0)
			return;

		tbl_ptr = pi->calibration_cache.txcal_coeffs_5G;
		loft_comp = &pi->calibration_cache.txcal_coeffs_5G[5];
	}

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 4, 80, 16, tbl_ptr);

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		txcal_coeffs_bphy[0] = tbl_ptr[0];
		txcal_coeffs_bphy[1] = tbl_ptr[1];
		txcal_coeffs_bphy[2] = tbl_ptr[2];
		txcal_coeffs_bphy[3] = tbl_ptr[3];
	} else {
		txcal_coeffs_bphy[0] = 0;
		txcal_coeffs_bphy[1] = 0;
		txcal_coeffs_bphy[2] = 0;
		txcal_coeffs_bphy[3] = 0;
	}

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 4, 88, 16,
				 txcal_coeffs_bphy);

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 2, 85, 16, loft_comp);

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 2, 93, 16, loft_comp);

	if (NREV_LT(pi->pubpi.phy_rev, 2))
		wlc_phy_tx_iq_war_nphy(pi);

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			txcal_radio_regs =
				pi->calibration_cache.txcal_radio_regs_2G;
		} else if (NREV_GE(pi->pubpi.phy_rev, 3)) {

			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_I |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_2G[0]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_Q |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_2G[1]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_I |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_2G[2]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_Q |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_2G[3]);

			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_I |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_2G[4]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_Q |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_2G[5]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_I |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_2G[6]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_Q |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_2G[7]);
		} else {
			write_radio_reg(pi, RADIO_2055_CORE1_TX_VOS_CNCL,
					pi->calibration_cache.
					txcal_radio_regs_2G[0]);
			write_radio_reg(pi, RADIO_2055_CORE2_TX_VOS_CNCL,
					pi->calibration_cache.
					txcal_radio_regs_2G[1]);
			write_radio_reg(pi, RADIO_2055_CORE1_TX_BB_MXGM,
					pi->calibration_cache.
					txcal_radio_regs_2G[2]);
			write_radio_reg(pi, RADIO_2055_CORE2_TX_BB_MXGM,
					pi->calibration_cache.
					txcal_radio_regs_2G[3]);
		}

		wlc_phy_rx_iq_coeffs_nphy(pi, 1,
					  &pi->calibration_cache.
					  rxcal_coeffs_2G);
	} else {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			txcal_radio_regs =
				pi->calibration_cache.txcal_radio_regs_5G;
		} else if (NREV_GE(pi->pubpi.phy_rev, 3)) {

			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_I |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_5G[0]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_Q |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_5G[1]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_I |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_5G[2]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_FINE_Q |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_5G[3]);

			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_I |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_5G[4]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_Q |
					RADIO_2056_TX0,
					pi->calibration_cache.
					txcal_radio_regs_5G[5]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_I |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_5G[6]);
			write_radio_reg(pi,
					RADIO_2056_TX_LOFT_COARSE_Q |
					RADIO_2056_TX1,
					pi->calibration_cache.
					txcal_radio_regs_5G[7]);
		} else {
			write_radio_reg(pi, RADIO_2055_CORE1_TX_VOS_CNCL,
					pi->calibration_cache.
					txcal_radio_regs_5G[0]);
			write_radio_reg(pi, RADIO_2055_CORE2_TX_VOS_CNCL,
					pi->calibration_cache.
					txcal_radio_regs_5G[1]);
			write_radio_reg(pi, RADIO_2055_CORE1_TX_BB_MXGM,
					pi->calibration_cache.
					txcal_radio_regs_5G[2]);
			write_radio_reg(pi, RADIO_2055_CORE2_TX_BB_MXGM,
					pi->calibration_cache.
					txcal_radio_regs_5G[3]);
		}

		wlc_phy_rx_iq_coeffs_nphy(pi, 1,
					  &pi->calibration_cache.
					  rxcal_coeffs_5G);
	}

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		for (coreNum = 0; coreNum <= 1; coreNum++) {

			WRITE_RADIO_REG3(pi, RADIO_2057, TX, coreNum,
					 LOFT_FINE_I,
					 txcal_radio_regs[2 * coreNum]);
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, coreNum,
					 LOFT_FINE_Q,
					 txcal_radio_regs[2 * coreNum + 1]);

			WRITE_RADIO_REG3(pi, RADIO_2057, TX, coreNum,
					 LOFT_COARSE_I,
					 txcal_radio_regs[2 * coreNum + 4]);
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, coreNum,
					 LOFT_COARSE_Q,
					 txcal_radio_regs[2 * coreNum + 5]);
		}
	}
}