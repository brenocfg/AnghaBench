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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tse_pcs_base; } ;
struct socfpga_dwmac {int reg_offset; int reg_shift; int /*<<< orphan*/  dev; TYPE_1__ pcs; int /*<<< orphan*/  stmmac_rst; int /*<<< orphan*/  stmmac_ocp_rst; scalar_t__ f2h_ptp_ref_clk; scalar_t__ splitter_base; struct regmap* sys_mgr_base_addr; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PHY_INTERFACE_MODE_GMII ; 
 int PHY_INTERFACE_MODE_MII ; 
 int PHY_INTERFACE_MODE_SGMII ; 
 int SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII ; 
 int SYSMGR_EMACGRP_CTRL_PHYSEL_MASK ; 
 int SYSMGR_EMACGRP_CTRL_PTP_REF_CLK_MASK ; 
 int SYSMGR_FPGAGRP_MODULE_EMAC ; 
 int SYSMGR_FPGAGRP_MODULE_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int socfpga_get_plat_phymode (struct socfpga_dwmac*) ; 
 scalar_t__ socfpga_set_phy_mode_common (int,int*) ; 
 scalar_t__ tse_pcs_init (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int socfpga_gen5_set_phy_mode(struct socfpga_dwmac *dwmac)
{
	struct regmap *sys_mgr_base_addr = dwmac->sys_mgr_base_addr;
	int phymode = socfpga_get_plat_phymode(dwmac);
	u32 reg_offset = dwmac->reg_offset;
	u32 reg_shift = dwmac->reg_shift;
	u32 ctrl, val, module;

	if (socfpga_set_phy_mode_common(phymode, &val)) {
		dev_err(dwmac->dev, "bad phy mode %d\n", phymode);
		return -EINVAL;
	}

	/* Overwrite val to GMII if splitter core is enabled. The phymode here
	 * is the actual phy mode on phy hardware, but phy interface from
	 * EMAC core is GMII.
	 */
	if (dwmac->splitter_base)
		val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII;

	/* Assert reset to the enet controller before changing the phy mode */
	reset_control_assert(dwmac->stmmac_ocp_rst);
	reset_control_assert(dwmac->stmmac_rst);

	regmap_read(sys_mgr_base_addr, reg_offset, &ctrl);
	ctrl &= ~(SYSMGR_EMACGRP_CTRL_PHYSEL_MASK << reg_shift);
	ctrl |= val << reg_shift;

	if (dwmac->f2h_ptp_ref_clk ||
	    phymode == PHY_INTERFACE_MODE_MII ||
	    phymode == PHY_INTERFACE_MODE_GMII ||
	    phymode == PHY_INTERFACE_MODE_SGMII) {
		ctrl |= SYSMGR_EMACGRP_CTRL_PTP_REF_CLK_MASK << (reg_shift / 2);
		regmap_read(sys_mgr_base_addr, SYSMGR_FPGAGRP_MODULE_REG,
			    &module);
		module |= (SYSMGR_FPGAGRP_MODULE_EMAC << (reg_shift / 2));
		regmap_write(sys_mgr_base_addr, SYSMGR_FPGAGRP_MODULE_REG,
			     module);
	} else {
		ctrl &= ~(SYSMGR_EMACGRP_CTRL_PTP_REF_CLK_MASK << (reg_shift / 2));
	}

	regmap_write(sys_mgr_base_addr, reg_offset, ctrl);

	/* Deassert reset for the phy configuration to be sampled by
	 * the enet controller, and operation to start in requested mode
	 */
	reset_control_deassert(dwmac->stmmac_ocp_rst);
	reset_control_deassert(dwmac->stmmac_rst);
	if (phymode == PHY_INTERFACE_MODE_SGMII) {
		if (tse_pcs_init(dwmac->pcs.tse_pcs_base, &dwmac->pcs) != 0) {
			dev_err(dwmac->dev, "Unable to initialize TSE PCS");
			return -EINVAL;
		}
	}

	return 0;
}