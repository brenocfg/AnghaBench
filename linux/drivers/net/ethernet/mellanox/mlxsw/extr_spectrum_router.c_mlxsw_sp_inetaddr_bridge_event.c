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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_rif_params {struct net_device* dev; } ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct mlxsw_sp_rif*) ; 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int PTR_ERR (struct mlxsw_sp_rif*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_create (struct mlxsw_sp*,struct mlxsw_sp_rif_params*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_destroy (struct mlxsw_sp_rif*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_inetaddr_bridge_event(struct mlxsw_sp *mlxsw_sp,
					  struct net_device *l3_dev,
					  unsigned long event,
					  struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_rif_params params = {
		.dev = l3_dev,
	};
	struct mlxsw_sp_rif *rif;

	switch (event) {
	case NETDEV_UP:
		rif = mlxsw_sp_rif_create(mlxsw_sp, &params, extack);
		if (IS_ERR(rif))
			return PTR_ERR(rif);
		break;
	case NETDEV_DOWN:
		rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, l3_dev);
		mlxsw_sp_rif_destroy(rif);
		break;
	}

	return 0;
}