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
typedef  int /*<<< orphan*/  u16 ;
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int conn_type; } ;
struct mii_bus {struct xgbe_prv_data* priv; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int XGBE_CONN_TYPE_MDIO ; 
 int XGBE_CONN_TYPE_SFP ; 
 int xgbe_phy_get_comm_ownership (struct xgbe_prv_data*) ; 
 int xgbe_phy_i2c_mii_write (struct xgbe_prv_data*,int,int /*<<< orphan*/ ) ; 
 int xgbe_phy_mdio_mii_write (struct xgbe_prv_data*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_phy_put_comm_ownership (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_mii_write(struct mii_bus *mii, int addr, int reg, u16 val)
{
	struct xgbe_prv_data *pdata = mii->priv;
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	int ret;

	ret = xgbe_phy_get_comm_ownership(pdata);
	if (ret)
		return ret;

	if (phy_data->conn_type == XGBE_CONN_TYPE_SFP)
		ret = xgbe_phy_i2c_mii_write(pdata, reg, val);
	else if (phy_data->conn_type & XGBE_CONN_TYPE_MDIO)
		ret = xgbe_phy_mdio_mii_write(pdata, addr, reg, val);
	else
		ret = -ENOTSUPP;

	xgbe_phy_put_comm_ownership(pdata);

	return ret;
}