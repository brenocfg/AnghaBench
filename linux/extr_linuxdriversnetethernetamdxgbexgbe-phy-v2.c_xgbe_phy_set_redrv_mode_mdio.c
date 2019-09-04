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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int (* write_ext_mii_regs ) (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;
struct xgbe_prv_data {TYPE_1__ hw_if; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int redrv_lane; int /*<<< orphan*/  redrv_addr; } ;
typedef  enum xgbe_phy_redrv_mode { ____Placeholder_xgbe_phy_redrv_mode } xgbe_phy_redrv_mode ;

/* Variables and functions */
 scalar_t__ XGBE_PHY_REDRV_MODE_REG ; 
 int stub1 (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int xgbe_phy_set_redrv_mode_mdio(struct xgbe_prv_data *pdata,
					enum xgbe_phy_redrv_mode mode)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	u16 redrv_reg, redrv_val;

	redrv_reg = XGBE_PHY_REDRV_MODE_REG + (phy_data->redrv_lane * 0x1000);
	redrv_val = (u16)mode;

	return pdata->hw_if.write_ext_mii_regs(pdata, phy_data->redrv_addr,
					       redrv_reg, redrv_val);
}