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
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGEADDR 130 
#define  NETDEV_CHANGEMTU 129 
#define  NETDEV_PRE_CHANGEADDR 128 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,struct net_device*) ; 
 int mlxsw_sp_router_port_change_event (struct mlxsw_sp*,struct mlxsw_sp_rif*) ; 
 int mlxsw_sp_router_port_pre_changeaddr_event (struct mlxsw_sp_rif*,void*) ; 

int mlxsw_sp_netdevice_router_port_event(struct net_device *dev,
					 unsigned long event, void *ptr)
{
	struct mlxsw_sp *mlxsw_sp;
	struct mlxsw_sp_rif *rif;

	mlxsw_sp = mlxsw_sp_lower_get(dev);
	if (!mlxsw_sp)
		return 0;

	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, dev);
	if (!rif)
		return 0;

	switch (event) {
	case NETDEV_CHANGEMTU: /* fall through */
	case NETDEV_CHANGEADDR:
		return mlxsw_sp_router_port_change_event(mlxsw_sp, rif);
	case NETDEV_PRE_CHANGEADDR:
		return mlxsw_sp_router_port_pre_changeaddr_event(rif, ptr);
	}

	return 0;
}