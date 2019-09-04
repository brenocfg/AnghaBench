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
struct mlxsw_sp_rif {int /*<<< orphan*/  nexthop_list; } ;
struct mlxsw_sp_nexthop {int /*<<< orphan*/  rif_list_node; struct mlxsw_sp_rif* rif; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_nexthop_rif_init(struct mlxsw_sp_nexthop *nh,
				      struct mlxsw_sp_rif *rif)
{
	if (nh->rif)
		return;

	nh->rif = rif;
	list_add(&nh->rif_list_node, &rif->nexthop_list);
}