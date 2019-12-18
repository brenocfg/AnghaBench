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
struct xgbe_phy_data {scalar_t__ conn_type; scalar_t__ mdio_reset; } ;

/* Variables and functions */
 scalar_t__ XGBE_CONN_TYPE_MDIO ; 
 scalar_t__ XGBE_MDIO_RESET_I2C_GPIO ; 
 scalar_t__ XGBE_MDIO_RESET_INT_GPIO ; 
 int xgbe_phy_get_comm_ownership (struct xgbe_prv_data*) ; 
 int xgbe_phy_i2c_mdio_reset (struct xgbe_prv_data*) ; 
 int xgbe_phy_int_mdio_reset (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_put_comm_ownership (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_mdio_reset(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	int ret;

	if (phy_data->conn_type != XGBE_CONN_TYPE_MDIO)
		return 0;

	ret = xgbe_phy_get_comm_ownership(pdata);
	if (ret)
		return ret;

	if (phy_data->mdio_reset == XGBE_MDIO_RESET_I2C_GPIO)
		ret = xgbe_phy_i2c_mdio_reset(pdata);
	else if (phy_data->mdio_reset == XGBE_MDIO_RESET_INT_GPIO)
		ret = xgbe_phy_int_mdio_reset(pdata);

	xgbe_phy_put_comm_ownership(pdata);

	return ret;
}