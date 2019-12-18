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
struct mlxsw_sp_nexthop {struct mlxsw_sp_ipip_entry* ipip_entry; } ;
struct mlxsw_sp_ipip_entry {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_nexthop_neigh_update (struct mlxsw_sp_nexthop*,int) ; 

__attribute__((used)) static void mlxsw_sp_nexthop_ipip_fini(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_nexthop *nh)
{
	struct mlxsw_sp_ipip_entry *ipip_entry = nh->ipip_entry;

	if (!ipip_entry)
		return;

	__mlxsw_sp_nexthop_neigh_update(nh, true);
	nh->ipip_entry = NULL;
}