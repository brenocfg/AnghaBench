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
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy_lcnphy {int /*<<< orphan*/  lcnphy_noise_samples; int /*<<< orphan*/  lcnphy_rawtempsense; int /*<<< orphan*/  lcnphy_cal_temper; scalar_t__ lcnphy_cal_counter; } ;
struct TYPE_5__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_4__* sh; TYPE_3__* d11core; int /*<<< orphan*/  radio_chanspec; TYPE_1__ u; } ;
struct TYPE_8__ {int boardflags; } ;
struct TYPE_7__ {TYPE_2__* bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  drv_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_CLK_INIT_MODE_TXRX2X ; 
 int BFL_FEM ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXED_TXPWR ; 
 int /*<<< orphan*/  LCNPHY_NOISE_SAMPLES_DEFAULT ; 
 int /*<<< orphan*/  LCNPHY_TX_PWR_CTRL_HW ; 
 int /*<<< orphan*/  PHY_PERICAL_PHYINIT ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  bcma_chipco_chipctl_maskset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bcma_chipco_regctl_maskset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_lcnphy_afe_clk_init (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_agc_temp_init (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_baseband_init (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_calib_modes (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_radio_init (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_by_index (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_temp_adj (struct brcms_phy*) ; 
 scalar_t__ wlc_lcnphy_tempsense_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_pwr_ctrl_init (struct brcms_phy_pub*) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_set (struct brcms_phy_pub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_phy_init_lcnphy(struct brcms_phy *pi)
{
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	pi_lcn->lcnphy_cal_counter = 0;
	pi_lcn->lcnphy_cal_temper = pi_lcn->lcnphy_rawtempsense;

	or_phy_reg(pi, 0x44a, 0x80);
	and_phy_reg(pi, 0x44a, 0x7f);

	wlc_lcnphy_afe_clk_init(pi, AFE_CLK_INIT_MODE_TXRX2X);

	write_phy_reg(pi, 0x60a, 160);

	write_phy_reg(pi, 0x46a, 25);

	wlc_lcnphy_baseband_init(pi);

	wlc_lcnphy_radio_init(pi);

	if (CHSPEC_IS2G(pi->radio_chanspec))
		wlc_lcnphy_tx_pwr_ctrl_init((struct brcms_phy_pub *) pi);

	wlc_phy_chanspec_set((struct brcms_phy_pub *) pi, pi->radio_chanspec);

	bcma_chipco_regctl_maskset(&pi->d11core->bus->drv_cc, 0, ~0xf, 0x9);

	bcma_chipco_chipctl_maskset(&pi->d11core->bus->drv_cc, 0, 0x0,
				    0x03CDDDDD);

	if ((pi->sh->boardflags & BFL_FEM)
	    && wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi))
		wlc_lcnphy_set_tx_pwr_by_index(pi, FIXED_TXPWR);

	wlc_lcnphy_agc_temp_init(pi);

	wlc_lcnphy_temp_adj(pi);

	mod_phy_reg(pi, 0x448, (0x1 << 14), (1) << 14);

	udelay(100);
	mod_phy_reg(pi, 0x448, (0x1 << 14), (0) << 14);

	wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_HW);
	pi_lcn->lcnphy_noise_samples = LCNPHY_NOISE_SAMPLES_DEFAULT;
	wlc_lcnphy_calib_modes(pi, PHY_PERICAL_PHYINIT);
}