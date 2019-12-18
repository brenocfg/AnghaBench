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
struct net_device {int dummy; } ;
struct mlxsw_sp_ipip_entry {int dummy; } ;
struct mlxsw_sp {TYPE_2__* router; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_4__ {TYPE_1__** ipip_ops_arr; } ;
struct TYPE_3__ {int ul_proto; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_ipip_entry*) ; 
 int PTR_ERR (struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_demote_tunnel_by_saddr (struct mlxsw_sp*,int,union mlxsw_sp_l3addr,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_dev_ul_tb_id (struct net_device*) ; 
 struct mlxsw_sp_ipip_entry* mlxsw_sp_ipip_entry_create (struct mlxsw_sp*,int,struct net_device*) ; 
 union mlxsw_sp_l3addr mlxsw_sp_ipip_netdev_saddr (int,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_netdev_ipip_type (struct mlxsw_sp*,struct net_device*,int*) ; 
 scalar_t__ mlxsw_sp_netdevice_ipip_can_offload (struct mlxsw_sp*,struct net_device*,int) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_ipip_ol_reg_event(struct mlxsw_sp *mlxsw_sp,
						struct net_device *ol_dev)
{
	struct mlxsw_sp_ipip_entry *ipip_entry;
	enum mlxsw_sp_l3proto ul_proto;
	enum mlxsw_sp_ipip_type ipipt;
	union mlxsw_sp_l3addr saddr;
	u32 ul_tb_id;

	mlxsw_sp_netdev_ipip_type(mlxsw_sp, ol_dev, &ipipt);
	if (mlxsw_sp_netdevice_ipip_can_offload(mlxsw_sp, ol_dev, ipipt)) {
		ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ol_dev);
		ul_proto = mlxsw_sp->router->ipip_ops_arr[ipipt]->ul_proto;
		saddr = mlxsw_sp_ipip_netdev_saddr(ul_proto, ol_dev);
		if (!mlxsw_sp_ipip_demote_tunnel_by_saddr(mlxsw_sp, ul_proto,
							  saddr, ul_tb_id,
							  NULL)) {
			ipip_entry = mlxsw_sp_ipip_entry_create(mlxsw_sp, ipipt,
								ol_dev);
			if (IS_ERR(ipip_entry))
				return PTR_ERR(ipip_entry);
		}
	}

	return 0;
}