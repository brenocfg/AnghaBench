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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;
struct dcb_app {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcb_ieee_delapp (struct net_device*,struct dcb_app*) ; 
 int dcb_ieee_setapp (struct net_device*,struct dcb_app*) ; 
 int mlxsw_sp_dcbnl_app_validate (struct net_device*,struct dcb_app*) ; 
 int mlxsw_sp_port_dcb_app_update (struct mlxsw_sp_port*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_dcbnl_ieee_setapp(struct net_device *dev,
				      struct dcb_app *app)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	int err;

	err = mlxsw_sp_dcbnl_app_validate(dev, app);
	if (err)
		return err;

	err = dcb_ieee_setapp(dev, app);
	if (err)
		return err;

	err = mlxsw_sp_port_dcb_app_update(mlxsw_sp_port);
	if (err)
		goto err_update;

	return 0;

err_update:
	dcb_ieee_delapp(dev, app);
	return err;
}