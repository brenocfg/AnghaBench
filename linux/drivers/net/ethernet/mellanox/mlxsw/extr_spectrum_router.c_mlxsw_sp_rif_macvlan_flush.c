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
struct mlxsw_sp_rif {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_rif_macvlan_flush ; 
 int netdev_walk_all_upper_dev_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_is_macvlan_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_rif_macvlan_flush(struct mlxsw_sp_rif *rif)
{
	if (!netif_is_macvlan_port(rif->dev))
		return 0;

	netdev_warn(rif->dev, "Router interface is deleted. Upper macvlans will not work\n");
	return netdev_walk_all_upper_dev_rcu(rif->dev,
					     __mlxsw_sp_rif_macvlan_flush, rif);
}