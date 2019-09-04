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
 int mlxsw_sp_ipip_entry_find_by_ul_dev (struct mlxsw_sp const*,struct net_device const*,int /*<<< orphan*/ *) ; 

bool mlxsw_sp_netdev_is_ipip_ul(const struct mlxsw_sp *mlxsw_sp,
				const struct net_device *dev)
{
	return mlxsw_sp_ipip_entry_find_by_ul_dev(mlxsw_sp, dev, NULL);
}