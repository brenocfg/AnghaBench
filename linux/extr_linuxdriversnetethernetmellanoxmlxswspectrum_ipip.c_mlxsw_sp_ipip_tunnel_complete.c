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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
struct net_device {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
 union mlxsw_sp_l3addr mlxsw_sp_ipip_netdev_daddr (int,struct net_device const*) ; 
 union mlxsw_sp_l3addr mlxsw_sp_ipip_netdev_saddr (int,struct net_device const*) ; 
 int /*<<< orphan*/  mlxsw_sp_l3addr_is_zero (union mlxsw_sp_l3addr) ; 

__attribute__((used)) static bool mlxsw_sp_ipip_tunnel_complete(enum mlxsw_sp_l3proto proto,
					  const struct net_device *ol_dev)
{
	union mlxsw_sp_l3addr saddr = mlxsw_sp_ipip_netdev_saddr(proto, ol_dev);
	union mlxsw_sp_l3addr daddr = mlxsw_sp_ipip_netdev_daddr(proto, ol_dev);

	/* Tunnels with unset local or remote address are valid in Linux and
	 * used for lightweight tunnels (LWT) and Non-Broadcast Multi-Access
	 * (NBMA) tunnels. In principle these can be offloaded, but the driver
	 * currently doesn't support this. So punt.
	 */
	return !mlxsw_sp_l3addr_is_zero(saddr) &&
	       !mlxsw_sp_l3addr_is_zero(daddr);
}