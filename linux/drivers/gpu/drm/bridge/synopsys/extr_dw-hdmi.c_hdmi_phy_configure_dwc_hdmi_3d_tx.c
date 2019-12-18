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
struct dw_hdmi_plat_data {struct dw_hdmi_phy_config* phy_config; struct dw_hdmi_curr_ctrl* cur_ctr; struct dw_hdmi_mpll_config* mpll_cfg; } ;
struct dw_hdmi_phy_config {unsigned long mpixelclock; int /*<<< orphan*/  vlev_ctr; int /*<<< orphan*/  sym_ctr; int /*<<< orphan*/  term; } ;
struct dw_hdmi_mpll_config {unsigned long mpixelclock; TYPE_1__* res; } ;
struct dw_hdmi_curr_ctrl {unsigned long mpixelclock; int /*<<< orphan*/ * curr; } ;
struct dw_hdmi {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gmp; int /*<<< orphan*/  cpce; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_CKCALCTRL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_CKCALCTRL_OVERRIDE ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_CKSYMTXCTRL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_CPCE_CTRL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_CURRCTRL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_GMPCTRL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_MSM_CTRL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_FB_CLK ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_PLLPHBYCTRL ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_TXTERM ; 
 int /*<<< orphan*/  HDMI_3D_TX_PHY_VLEVCTRL ; 
 int /*<<< orphan*/  dw_hdmi_phy_i2c_write (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_phy_configure_dwc_hdmi_3d_tx(struct dw_hdmi *hdmi,
		const struct dw_hdmi_plat_data *pdata,
		unsigned long mpixelclock)
{
	const struct dw_hdmi_mpll_config *mpll_config = pdata->mpll_cfg;
	const struct dw_hdmi_curr_ctrl *curr_ctrl = pdata->cur_ctr;
	const struct dw_hdmi_phy_config *phy_config = pdata->phy_config;

	/* TOFIX Will need 420 specific PHY configuration tables */

	/* PLL/MPLL Cfg - always match on final entry */
	for (; mpll_config->mpixelclock != ~0UL; mpll_config++)
		if (mpixelclock <= mpll_config->mpixelclock)
			break;

	for (; curr_ctrl->mpixelclock != ~0UL; curr_ctrl++)
		if (mpixelclock <= curr_ctrl->mpixelclock)
			break;

	for (; phy_config->mpixelclock != ~0UL; phy_config++)
		if (mpixelclock <= phy_config->mpixelclock)
			break;

	if (mpll_config->mpixelclock == ~0UL ||
	    curr_ctrl->mpixelclock == ~0UL ||
	    phy_config->mpixelclock == ~0UL)
		return -EINVAL;

	dw_hdmi_phy_i2c_write(hdmi, mpll_config->res[0].cpce,
			      HDMI_3D_TX_PHY_CPCE_CTRL);
	dw_hdmi_phy_i2c_write(hdmi, mpll_config->res[0].gmp,
			      HDMI_3D_TX_PHY_GMPCTRL);
	dw_hdmi_phy_i2c_write(hdmi, curr_ctrl->curr[0],
			      HDMI_3D_TX_PHY_CURRCTRL);

	dw_hdmi_phy_i2c_write(hdmi, 0, HDMI_3D_TX_PHY_PLLPHBYCTRL);
	dw_hdmi_phy_i2c_write(hdmi, HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_FB_CLK,
			      HDMI_3D_TX_PHY_MSM_CTRL);

	dw_hdmi_phy_i2c_write(hdmi, phy_config->term, HDMI_3D_TX_PHY_TXTERM);
	dw_hdmi_phy_i2c_write(hdmi, phy_config->sym_ctr,
			      HDMI_3D_TX_PHY_CKSYMTXCTRL);
	dw_hdmi_phy_i2c_write(hdmi, phy_config->vlev_ctr,
			      HDMI_3D_TX_PHY_VLEVCTRL);

	/* Override and disable clock termination. */
	dw_hdmi_phy_i2c_write(hdmi, HDMI_3D_TX_PHY_CKCALCTRL_OVERRIDE,
			      HDMI_3D_TX_PHY_CKCALCTRL);

	return 0;
}