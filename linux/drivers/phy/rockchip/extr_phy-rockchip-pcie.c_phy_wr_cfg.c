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
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_pcie_phy {TYPE_1__* phy_data; int /*<<< orphan*/  reg_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcie_conf; } ;

/* Variables and functions */
 int HIWORD_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_CFG_ADDR_MASK ; 
 int /*<<< orphan*/  PHY_CFG_ADDR_SHIFT ; 
 int /*<<< orphan*/  PHY_CFG_DATA_MASK ; 
 int /*<<< orphan*/  PHY_CFG_DATA_SHIFT ; 
 int /*<<< orphan*/  PHY_CFG_WR_DISABLE ; 
 int /*<<< orphan*/  PHY_CFG_WR_ENABLE ; 
 int /*<<< orphan*/  PHY_CFG_WR_MASK ; 
 int /*<<< orphan*/  PHY_CFG_WR_SHIFT ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void phy_wr_cfg(struct rockchip_pcie_phy *rk_phy,
			      u32 addr, u32 data)
{
	regmap_write(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(data,
				   PHY_CFG_DATA_MASK,
				   PHY_CFG_DATA_SHIFT) |
		     HIWORD_UPDATE(addr,
				   PHY_CFG_ADDR_MASK,
				   PHY_CFG_ADDR_SHIFT));
	udelay(1);
	regmap_write(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_WR_ENABLE,
				   PHY_CFG_WR_MASK,
				   PHY_CFG_WR_SHIFT));
	udelay(1);
	regmap_write(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_WR_DISABLE,
				   PHY_CFG_WR_MASK,
				   PHY_CFG_WR_SHIFT));
}