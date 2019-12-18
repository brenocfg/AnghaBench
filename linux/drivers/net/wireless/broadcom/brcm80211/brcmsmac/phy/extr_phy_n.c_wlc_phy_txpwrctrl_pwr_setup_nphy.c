#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int /*<<< orphan*/  phy_rev; } ;
struct TYPE_6__ {scalar_t__ tssipos; } ;
struct brcms_phy {int* adj_pwr_tbl_nphy; scalar_t__ phyhang_avoid; TYPE_4__ pubpi; TYPE_3__* sh; int /*<<< orphan*/  d11core; int /*<<< orphan*/  radio_chanspec; TYPE_2__ srom_fem2g; scalar_t__ tx_power_max; TYPE_1__* nphy_pwrctrl_info; } ;
typedef  int s8 ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_7__ {int sromrev; int /*<<< orphan*/  physhim; int /*<<< orphan*/  corerev; } ;
struct TYPE_5__ {int idle_tssi_2g; int pwrdet_2g_a1; int pwrdet_2g_b0; int pwrdet_2g_b1; int idle_tssi_5g; int pwrdet_5gl_a1; int pwrdet_5gl_b0; int pwrdet_5gl_b1; int pwrdet_5gm_a1; int pwrdet_5gm_b0; int pwrdet_5gm_b1; int pwrdet_5gh_a1; int pwrdet_5gh_b0; int pwrdet_5gh_b1; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_IS (int /*<<< orphan*/ ,int) ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  MCTL_PHYLOCK ; 
 int NPHY_TBL_ID_CORE1TXPWRCTL ; 
 int NPHY_TBL_ID_CORE2TXPWRCTL ; 
 int NPHY_TxPwrCtrlCmd_pwrIndex_init ; 
 int NPHY_TxPwrCtrlCmd_pwrIndex_init_rev7 ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_GT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 int RADIO_2056_TX0 ; 
 int RADIO_2056_TX1 ; 
 int RADIO_2056_TX_TX_SSI_MUX ; 
 int /*<<< orphan*/  RADIO_2057 ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  TX_SSI_MUX ; 
#define  WL_CHAN_FREQ_RANGE_2G 131 
#define  WL_CHAN_FREQ_RANGE_5GH 130 
#define  WL_CHAN_FREQ_RANGE_5GL 129 
#define  WL_CHAN_FREQ_RANGE_5GM 128 
 int /*<<< orphan*/  WRITE_RADIO_REG3 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlapi_bmac_mctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wlc_phy_get_chan_freq_range_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_limit_to_tbl_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_txpwrctrl_pwr_setup_nphy(struct brcms_phy *pi)
{
	u32 idx;
	s16 a1[2], b0[2], b1[2];
	s8 target_pwr_qtrdbm[2];
	s32 num, den, pwr_est;
	u8 chan_freq_range;
	u8 idle_tssi[2];
	u32 tbl_id, tbl_len, tbl_offset;
	u32 regval[64];
	u8 core;

	if (D11REV_IS(pi->sh->corerev, 11) || D11REV_IS(pi->sh->corerev, 12)) {
		wlapi_bmac_mctrl(pi->sh->physhim, MCTL_PHYLOCK, MCTL_PHYLOCK);
		(void)bcma_read32(pi->d11core, D11REGOFFS(maccontrol));
		udelay(1);
	}

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, true);

	or_phy_reg(pi, 0x122, (0x1 << 0));

	if (NREV_GE(pi->pubpi.phy_rev, 3))
		and_phy_reg(pi, 0x1e7, (u16) (~(0x1 << 15)));
	else
		or_phy_reg(pi, 0x1e7, (0x1 << 15));

	if (D11REV_IS(pi->sh->corerev, 11) || D11REV_IS(pi->sh->corerev, 12))
		wlapi_bmac_mctrl(pi->sh->physhim, MCTL_PHYLOCK, 0);

	if (pi->sh->sromrev < 4) {
		idle_tssi[0] = pi->nphy_pwrctrl_info[0].idle_tssi_2g;
		idle_tssi[1] = pi->nphy_pwrctrl_info[1].idle_tssi_2g;
		a1[0] = -424;
		a1[1] = -424;
		b0[0] = 5612;
		b0[1] = 5612;
		b1[1] = -1393;
		b1[0] = -1393;
	} else {

		chan_freq_range = wlc_phy_get_chan_freq_range_nphy(pi, 0);
		switch (chan_freq_range) {
		case WL_CHAN_FREQ_RANGE_2G:
			idle_tssi[0] = pi->nphy_pwrctrl_info[0].idle_tssi_2g;
			idle_tssi[1] = pi->nphy_pwrctrl_info[1].idle_tssi_2g;
			a1[0] = pi->nphy_pwrctrl_info[0].pwrdet_2g_a1;
			a1[1] = pi->nphy_pwrctrl_info[1].pwrdet_2g_a1;
			b0[0] = pi->nphy_pwrctrl_info[0].pwrdet_2g_b0;
			b0[1] = pi->nphy_pwrctrl_info[1].pwrdet_2g_b0;
			b1[0] = pi->nphy_pwrctrl_info[0].pwrdet_2g_b1;
			b1[1] = pi->nphy_pwrctrl_info[1].pwrdet_2g_b1;
			break;
		case WL_CHAN_FREQ_RANGE_5GL:
			idle_tssi[0] = pi->nphy_pwrctrl_info[0].idle_tssi_5g;
			idle_tssi[1] = pi->nphy_pwrctrl_info[1].idle_tssi_5g;
			a1[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gl_a1;
			a1[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gl_a1;
			b0[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gl_b0;
			b0[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gl_b0;
			b1[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gl_b1;
			b1[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gl_b1;
			break;
		case WL_CHAN_FREQ_RANGE_5GM:
			idle_tssi[0] = pi->nphy_pwrctrl_info[0].idle_tssi_5g;
			idle_tssi[1] = pi->nphy_pwrctrl_info[1].idle_tssi_5g;
			a1[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gm_a1;
			a1[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gm_a1;
			b0[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gm_b0;
			b0[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gm_b0;
			b1[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gm_b1;
			b1[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gm_b1;
			break;
		case WL_CHAN_FREQ_RANGE_5GH:
			idle_tssi[0] = pi->nphy_pwrctrl_info[0].idle_tssi_5g;
			idle_tssi[1] = pi->nphy_pwrctrl_info[1].idle_tssi_5g;
			a1[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gh_a1;
			a1[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gh_a1;
			b0[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gh_b0;
			b0[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gh_b0;
			b1[0] = pi->nphy_pwrctrl_info[0].pwrdet_5gh_b1;
			b1[1] = pi->nphy_pwrctrl_info[1].pwrdet_5gh_b1;
			break;
		default:
			idle_tssi[0] = pi->nphy_pwrctrl_info[0].idle_tssi_2g;
			idle_tssi[1] = pi->nphy_pwrctrl_info[1].idle_tssi_2g;
			a1[0] = -424;
			a1[1] = -424;
			b0[0] = 5612;
			b0[1] = 5612;
			b1[1] = -1393;
			b1[0] = -1393;
			break;
		}
	}

	/* use the provided transmit power */
	target_pwr_qtrdbm[0] = (s8) pi->tx_power_max;
	target_pwr_qtrdbm[1] = (s8) pi->tx_power_max;

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		if (pi->srom_fem2g.tssipos)
			or_phy_reg(pi, 0x1e9, (0x1 << 14));

		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			for (core = 0; core <= 1; core++) {
				if (PHY_IPA(pi)) {
					if (CHSPEC_IS2G(pi->radio_chanspec))
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TX_SSI_MUX,
								 0xe);
					else
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TX_SSI_MUX,
								 0xc);
				}
			}
		} else {
			if (PHY_IPA(pi)) {

				write_radio_reg(pi, RADIO_2056_TX_TX_SSI_MUX |
						RADIO_2056_TX0,
						(CHSPEC_IS5G
						 (pi->radio_chanspec)) ?
						 0xc : 0xe);
				write_radio_reg(pi,
						RADIO_2056_TX_TX_SSI_MUX |
						RADIO_2056_TX1,
						(CHSPEC_IS5G
						 (pi->radio_chanspec)) ?
						 0xc : 0xe);
			} else {

				write_radio_reg(pi, RADIO_2056_TX_TX_SSI_MUX |
						RADIO_2056_TX0, 0x11);
				write_radio_reg(pi, RADIO_2056_TX_TX_SSI_MUX |
						RADIO_2056_TX1, 0x11);
			}
		}
	}

	if (D11REV_IS(pi->sh->corerev, 11) || D11REV_IS(pi->sh->corerev, 12)) {
		wlapi_bmac_mctrl(pi->sh->physhim, MCTL_PHYLOCK, MCTL_PHYLOCK);
		(void)bcma_read32(pi->d11core, D11REGOFFS(maccontrol));
		udelay(1);
	}

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		mod_phy_reg(pi, 0x1e7, (0x7f << 0),
			    (NPHY_TxPwrCtrlCmd_pwrIndex_init_rev7 << 0));
	else
		mod_phy_reg(pi, 0x1e7, (0x7f << 0),
			    (NPHY_TxPwrCtrlCmd_pwrIndex_init << 0));

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		mod_phy_reg(pi, 0x222, (0xff << 0),
			    (NPHY_TxPwrCtrlCmd_pwrIndex_init_rev7 << 0));
	else if (NREV_GT(pi->pubpi.phy_rev, 1))
		mod_phy_reg(pi, 0x222, (0xff << 0),
			    (NPHY_TxPwrCtrlCmd_pwrIndex_init << 0));

	if (D11REV_IS(pi->sh->corerev, 11) || D11REV_IS(pi->sh->corerev, 12))
		wlapi_bmac_mctrl(pi->sh->physhim, MCTL_PHYLOCK, 0);

	write_phy_reg(pi, 0x1e8, (0x3 << 8) | (240 << 0));

	write_phy_reg(pi, 0x1e9,
		      (1 << 15) | (idle_tssi[0] << 0) | (idle_tssi[1] << 8));

	write_phy_reg(pi, 0x1ea,
		      (target_pwr_qtrdbm[0] << 0) |
		      (target_pwr_qtrdbm[1] << 8));

	tbl_len = 64;
	tbl_offset = 0;
	for (tbl_id = NPHY_TBL_ID_CORE1TXPWRCTL;
	     tbl_id <= NPHY_TBL_ID_CORE2TXPWRCTL; tbl_id++) {

		for (idx = 0; idx < tbl_len; idx++) {
			num = 8 *
			      (16 * b0[tbl_id - 26] + b1[tbl_id - 26] * idx);
			den = 32768 + a1[tbl_id - 26] * idx;
			pwr_est = max(DIV_ROUND_CLOSEST(4 * num, den), -8);
			if (NREV_LT(pi->pubpi.phy_rev, 3)) {
				if (idx <=
				    (uint) (31 - idle_tssi[tbl_id - 26] + 1))
					pwr_est =
						max(pwr_est,
						    target_pwr_qtrdbm
						    [tbl_id - 26] + 1);
			}
			regval[idx] = (u32) pwr_est;
		}
		wlc_phy_table_write_nphy(pi, tbl_id, tbl_len, tbl_offset, 32,
					 regval);
	}

	wlc_phy_txpwr_limit_to_tbl_nphy(pi);
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_CORE1TXPWRCTL, 84, 64, 8,
				 pi->adj_pwr_tbl_nphy);
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_CORE2TXPWRCTL, 84, 64, 8,
				 pi->adj_pwr_tbl_nphy);

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, false);
}