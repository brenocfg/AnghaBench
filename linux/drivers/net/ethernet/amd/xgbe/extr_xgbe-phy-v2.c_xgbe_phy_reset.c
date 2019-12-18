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
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int cur_mode; int /*<<< orphan*/  phydev; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
 int phy_init_hw (int /*<<< orphan*/ ) ; 
 int xgbe_phy_mdio_reset (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_power_off (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_set_mode (struct xgbe_prv_data*,int) ; 

__attribute__((used)) static int xgbe_phy_reset(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	enum xgbe_mode cur_mode;
	int ret;

	/* Reset by power cycling the PHY */
	cur_mode = phy_data->cur_mode;
	xgbe_phy_power_off(pdata);
	xgbe_phy_set_mode(pdata, cur_mode);

	if (!phy_data->phydev)
		return 0;

	/* Reset the external PHY */
	ret = xgbe_phy_mdio_reset(pdata);
	if (ret)
		return ret;

	return phy_init_hw(phy_data->phydev);
}