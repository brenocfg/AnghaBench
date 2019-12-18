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
struct rockchip_emmc_phy {int drive_impedance; scalar_t__ reg_offset; int /*<<< orphan*/  reg_base; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ GRF_EMMCPHY_CON0 ; 
 scalar_t__ GRF_EMMCPHY_CON6 ; 
 int /*<<< orphan*/  HIWORD_UPDATE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYCTRL_DR_MASK ; 
 int /*<<< orphan*/  PHYCTRL_DR_SHIFT ; 
 int PHYCTRL_OTAPDLYENA ; 
 int /*<<< orphan*/  PHYCTRL_OTAPDLYENA_MASK ; 
 int /*<<< orphan*/  PHYCTRL_OTAPDLYENA_SHIFT ; 
 int /*<<< orphan*/  PHYCTRL_OTAPDLYSEL_MASK ; 
 int /*<<< orphan*/  PHYCTRL_OTAPDLYSEL_SHIFT ; 
 int /*<<< orphan*/  PHYCTRL_PDB_PWR_ON ; 
 struct rockchip_emmc_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int rockchip_emmc_phy_power (struct phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_emmc_phy_power_on(struct phy *phy)
{
	struct rockchip_emmc_phy *rk_phy = phy_get_drvdata(phy);

	/* Drive impedance: from DTS */
	regmap_write(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON6,
		     HIWORD_UPDATE(rk_phy->drive_impedance,
				   PHYCTRL_DR_MASK,
				   PHYCTRL_DR_SHIFT));

	/* Output tap delay: enable */
	regmap_write(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON0,
		     HIWORD_UPDATE(PHYCTRL_OTAPDLYENA,
				   PHYCTRL_OTAPDLYENA_MASK,
				   PHYCTRL_OTAPDLYENA_SHIFT));

	/* Output tap delay */
	regmap_write(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON0,
		     HIWORD_UPDATE(4,
				   PHYCTRL_OTAPDLYSEL_MASK,
				   PHYCTRL_OTAPDLYSEL_SHIFT));

	/* Power up emmc phy analog blocks */
	return rockchip_emmc_phy_power(phy, PHYCTRL_PDB_PWR_ON);
}