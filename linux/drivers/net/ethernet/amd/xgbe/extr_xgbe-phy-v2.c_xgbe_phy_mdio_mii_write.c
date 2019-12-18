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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int (* write_ext_mii_regs ) (struct xgbe_prv_data*,int,int,int /*<<< orphan*/ ) ;} ;
struct xgbe_prv_data {TYPE_1__ hw_if; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ phydev_mode; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int MII_ADDR_C45 ; 
 scalar_t__ XGBE_MDIO_MODE_CL22 ; 
 scalar_t__ XGBE_MDIO_MODE_CL45 ; 
 int stub1 (struct xgbe_prv_data*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_phy_mdio_mii_write(struct xgbe_prv_data *pdata, int addr,
				   int reg, u16 val)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	if (reg & MII_ADDR_C45) {
		if (phy_data->phydev_mode != XGBE_MDIO_MODE_CL45)
			return -ENOTSUPP;
	} else {
		if (phy_data->phydev_mode != XGBE_MDIO_MODE_CL22)
			return -ENOTSUPP;
	}

	return pdata->hw_if.write_ext_mii_regs(pdata, addr, reg, val);
}