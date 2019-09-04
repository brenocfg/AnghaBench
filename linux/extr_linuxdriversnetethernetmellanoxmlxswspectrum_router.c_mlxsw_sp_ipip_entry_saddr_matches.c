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
typedef  scalar_t__ u32 ;
struct mlxsw_sp_ipip_entry {int ipipt; int /*<<< orphan*/  ol_dev; } ;
struct mlxsw_sp {TYPE_2__* router; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_4__ {TYPE_1__** ipip_ops_arr; } ;
struct TYPE_3__ {int const ul_proto; } ;

/* Variables and functions */
 scalar_t__ mlxsw_sp_ipip_dev_ul_tb_id (int /*<<< orphan*/ ) ; 
 union mlxsw_sp_l3addr mlxsw_sp_ipip_netdev_saddr (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sp_l3addr_eq (union mlxsw_sp_l3addr*,union mlxsw_sp_l3addr*) ; 

__attribute__((used)) static bool
mlxsw_sp_ipip_entry_saddr_matches(struct mlxsw_sp *mlxsw_sp,
				  const enum mlxsw_sp_l3proto ul_proto,
				  union mlxsw_sp_l3addr saddr,
				  u32 ul_tb_id,
				  struct mlxsw_sp_ipip_entry *ipip_entry)
{
	u32 tun_ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ipip_entry->ol_dev);
	enum mlxsw_sp_ipip_type ipipt = ipip_entry->ipipt;
	union mlxsw_sp_l3addr tun_saddr;

	if (mlxsw_sp->router->ipip_ops_arr[ipipt]->ul_proto != ul_proto)
		return false;

	tun_saddr = mlxsw_sp_ipip_netdev_saddr(ul_proto, ipip_entry->ol_dev);
	return tun_ul_tb_id == ul_tb_id &&
	       mlxsw_sp_l3addr_eq(&tun_saddr, &saddr);
}