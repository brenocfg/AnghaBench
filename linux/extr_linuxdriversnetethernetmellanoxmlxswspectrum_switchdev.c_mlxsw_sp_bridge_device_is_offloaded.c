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
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device const*) ; 

bool mlxsw_sp_bridge_device_is_offloaded(const struct mlxsw_sp *mlxsw_sp,
					 const struct net_device *br_dev)
{
	return !!mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
}