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
struct net_device {int mtu; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_port_headroom_set (struct mlxsw_sp_port*,int,int) ; 
 int mlxsw_sp_port_is_pause_en (struct mlxsw_sp_port*) ; 
 int mlxsw_sp_port_mtu_set (struct mlxsw_sp_port*,int) ; 
 int mlxsw_sp_span_port_mtu_update (struct mlxsw_sp_port*,int) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_port_change_mtu(struct net_device *dev, int mtu)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	bool pause_en = mlxsw_sp_port_is_pause_en(mlxsw_sp_port);
	int err;

	err = mlxsw_sp_port_headroom_set(mlxsw_sp_port, mtu, pause_en);
	if (err)
		return err;
	err = mlxsw_sp_span_port_mtu_update(mlxsw_sp_port, mtu);
	if (err)
		goto err_span_port_mtu_update;
	err = mlxsw_sp_port_mtu_set(mlxsw_sp_port, mtu);
	if (err)
		goto err_port_mtu_set;
	dev->mtu = mtu;
	return 0;

err_port_mtu_set:
	mlxsw_sp_span_port_mtu_update(mlxsw_sp_port, dev->mtu);
err_span_port_mtu_update:
	mlxsw_sp_port_headroom_set(mlxsw_sp_port, dev->mtu, pause_en);
	return err;
}