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
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct mlxsw_sp_port {TYPE_1__ periodic_hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct rtnl_link_stats64*,int /*<<< orphan*/ *,int) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
mlxsw_sp_port_get_stats64(struct net_device *dev,
			  struct rtnl_link_stats64 *stats)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	memcpy(stats, &mlxsw_sp_port->periodic_hw_stats.stats, sizeof(*stats));
}