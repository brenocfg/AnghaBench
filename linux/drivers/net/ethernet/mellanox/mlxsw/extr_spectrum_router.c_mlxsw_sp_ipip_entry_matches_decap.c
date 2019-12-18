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
struct mlxsw_sp_ipip_entry {int ipipt; } ;
struct mlxsw_sp {TYPE_2__* router; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_4__ {TYPE_1__** ipip_ops_arr; } ;
struct TYPE_3__ {int ul_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 scalar_t__ l3mdev_fib_table (struct net_device const*) ; 
 int mlxsw_sp_ipip_entry_saddr_matches (struct mlxsw_sp*,int,union mlxsw_sp_l3addr,int /*<<< orphan*/ ,struct mlxsw_sp_ipip_entry*) ; 

__attribute__((used)) static bool
mlxsw_sp_ipip_entry_matches_decap(struct mlxsw_sp *mlxsw_sp,
				  const struct net_device *ul_dev,
				  enum mlxsw_sp_l3proto ul_proto,
				  union mlxsw_sp_l3addr ul_dip,
				  struct mlxsw_sp_ipip_entry *ipip_entry)
{
	u32 ul_tb_id = l3mdev_fib_table(ul_dev) ? : RT_TABLE_MAIN;
	enum mlxsw_sp_ipip_type ipipt = ipip_entry->ipipt;

	if (mlxsw_sp->router->ipip_ops_arr[ipipt]->ul_proto != ul_proto)
		return false;

	return mlxsw_sp_ipip_entry_saddr_matches(mlxsw_sp, ul_proto, ul_dip,
						 ul_tb_id, ipip_entry);
}