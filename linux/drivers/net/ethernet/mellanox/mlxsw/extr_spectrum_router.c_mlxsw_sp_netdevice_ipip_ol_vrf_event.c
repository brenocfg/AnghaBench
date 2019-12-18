#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_ipip_entry {size_t ipipt; } ;
struct mlxsw_sp {TYPE_2__* router; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
struct TYPE_4__ {TYPE_1__** ipip_ops_arr; } ;
struct TYPE_3__ {int ul_proto; } ;

/* Variables and functions */
 int __mlxsw_sp_ipip_entry_update_tunnel (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*,int,int,int,struct netlink_ext_ack*) ; 
 scalar_t__ mlxsw_sp_ipip_demote_tunnel_by_saddr (struct mlxsw_sp*,int,union mlxsw_sp_l3addr,int /*<<< orphan*/ ,struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_dev_ul_tb_id (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_entry_demote_tunnel (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*) ; 
 struct mlxsw_sp_ipip_entry* mlxsw_sp_ipip_entry_find_by_ol_dev (struct mlxsw_sp*,struct net_device*) ; 
 union mlxsw_sp_l3addr mlxsw_sp_ipip_netdev_saddr (int,struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_ipip_ol_vrf_event(struct mlxsw_sp *mlxsw_sp,
						struct net_device *ol_dev,
						struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_ipip_entry *ipip_entry =
		mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);
	enum mlxsw_sp_l3proto ul_proto;
	union mlxsw_sp_l3addr saddr;
	u32 ul_tb_id;

	if (!ipip_entry)
		return 0;

	/* For flat configuration cases, moving overlay to a different VRF might
	 * cause local address conflict, and the conflicting tunnels need to be
	 * demoted.
	 */
	ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ol_dev);
	ul_proto = mlxsw_sp->router->ipip_ops_arr[ipip_entry->ipipt]->ul_proto;
	saddr = mlxsw_sp_ipip_netdev_saddr(ul_proto, ol_dev);
	if (mlxsw_sp_ipip_demote_tunnel_by_saddr(mlxsw_sp, ul_proto,
						 saddr, ul_tb_id,
						 ipip_entry)) {
		mlxsw_sp_ipip_entry_demote_tunnel(mlxsw_sp, ipip_entry);
		return 0;
	}

	return __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
						   true, false, false, extack);
}