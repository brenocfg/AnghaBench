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
struct net_device {int dummy; } ;
struct TYPE_2__ {struct ieee_maxrate* maxrate; } ;
struct mlxsw_sp_port {TYPE_1__ dcb; } ;
struct ieee_maxrate {int /*<<< orphan*/ * tc_maxrate; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  MLXSW_REG_QEEC_HIERARCY_SUBGROUP ; 
 int /*<<< orphan*/  memcpy (struct ieee_maxrate*,struct ieee_maxrate*,int) ; 
 int mlxsw_sp_port_ets_maxrate_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_dcbnl_ieee_setmaxrate(struct net_device *dev,
					  struct ieee_maxrate *maxrate)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct ieee_maxrate *my_maxrate = mlxsw_sp_port->dcb.maxrate;
	int err, i;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		err = mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
						    MLXSW_REG_QEEC_HIERARCY_SUBGROUP,
						    i, 0,
						    maxrate->tc_maxrate[i]);
		if (err) {
			netdev_err(dev, "Failed to set maxrate for TC %d\n", i);
			goto err_port_ets_maxrate_set;
		}
	}

	memcpy(mlxsw_sp_port->dcb.maxrate, maxrate, sizeof(*maxrate));

	return 0;

err_port_ets_maxrate_set:
	for (i--; i >= 0; i--)
		mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
					      MLXSW_REG_QEEC_HIERARCY_SUBGROUP,
					      i, 0, my_maxrate->tc_maxrate[i]);
	return err;
}