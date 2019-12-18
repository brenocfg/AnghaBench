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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_bridge_device_upper_rif_destroy ; 
 int /*<<< orphan*/  mlxsw_sp_rif_destroy_by_dev (struct mlxsw_sp*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_walk_all_upper_dev_rcu (struct net_device*,int /*<<< orphan*/ ,struct mlxsw_sp*) ; 

__attribute__((used)) static void mlxsw_sp_bridge_device_rifs_destroy(struct mlxsw_sp *mlxsw_sp,
						struct net_device *dev)
{
	mlxsw_sp_rif_destroy_by_dev(mlxsw_sp, dev);
	netdev_walk_all_upper_dev_rcu(dev,
				      mlxsw_sp_bridge_device_upper_rif_destroy,
				      mlxsw_sp);
}