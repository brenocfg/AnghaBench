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
struct mlxsw_sp_nexthop {struct mlxsw_sp_ipip_entry* ipip_entry; TYPE_1__* nh_grp; } ;
struct mlxsw_sp_ipip_entry {TYPE_2__* ol_lb; int /*<<< orphan*/  ol_dev; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  common; } ;
struct TYPE_3__ {int /*<<< orphan*/  gateway; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_nexthop_neigh_update (struct mlxsw_sp_nexthop*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_netdev_ul_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_rif_init (struct mlxsw_sp_nexthop*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_nexthop_ipip_init(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_nexthop *nh,
				       struct mlxsw_sp_ipip_entry *ipip_entry)
{
	bool removing;

	if (!nh->nh_grp->gateway || nh->ipip_entry)
		return;

	nh->ipip_entry = ipip_entry;
	removing = !mlxsw_sp_ipip_netdev_ul_up(ipip_entry->ol_dev);
	__mlxsw_sp_nexthop_neigh_update(nh, removing);
	mlxsw_sp_nexthop_rif_init(nh, &ipip_entry->ol_lb->common);
}