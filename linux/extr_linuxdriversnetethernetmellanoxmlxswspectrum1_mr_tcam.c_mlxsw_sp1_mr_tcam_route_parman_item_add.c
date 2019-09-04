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
struct mlxsw_sp_mr_route_key {int /*<<< orphan*/  proto; } ;
struct mlxsw_sp1_mr_tcam_route {int /*<<< orphan*/ * parman_prio; int /*<<< orphan*/  parman_item; } ;
struct mlxsw_sp1_mr_tcam_region {int /*<<< orphan*/ * parman_prios; int /*<<< orphan*/  parman; } ;
struct mlxsw_sp1_mr_tcam {int dummy; } ;
typedef  enum mlxsw_sp_mr_route_prio { ____Placeholder_mlxsw_sp_mr_route_prio } mlxsw_sp_mr_route_prio ;

/* Variables and functions */
 struct mlxsw_sp1_mr_tcam_region* mlxsw_sp1_mr_tcam_protocol_region (struct mlxsw_sp1_mr_tcam*,int /*<<< orphan*/ ) ; 
 int parman_item_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp1_mr_tcam_route_parman_item_add(struct mlxsw_sp1_mr_tcam *mr_tcam,
					struct mlxsw_sp1_mr_tcam_route *route,
					struct mlxsw_sp_mr_route_key *key,
					enum mlxsw_sp_mr_route_prio prio)
{
	struct mlxsw_sp1_mr_tcam_region *tcam_region;
	int err;

	tcam_region = mlxsw_sp1_mr_tcam_protocol_region(mr_tcam, key->proto);
	err = parman_item_add(tcam_region->parman,
			      &tcam_region->parman_prios[prio],
			      &route->parman_item);
	if (err)
		return err;

	route->parman_prio = &tcam_region->parman_prios[prio];
	return 0;
}