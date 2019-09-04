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
struct mlxsw_sp1_mr_tcam_route {int /*<<< orphan*/  parman_item; int /*<<< orphan*/  parman_prio; } ;
struct mlxsw_sp1_mr_tcam_region {int /*<<< orphan*/  parman; } ;
struct mlxsw_sp1_mr_tcam {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp1_mr_tcam_region* mlxsw_sp1_mr_tcam_protocol_region (struct mlxsw_sp1_mr_tcam*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parman_item_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp1_mr_tcam_route_parman_item_remove(struct mlxsw_sp1_mr_tcam *mr_tcam,
					   struct mlxsw_sp1_mr_tcam_route *route,
					   struct mlxsw_sp_mr_route_key *key)
{
	struct mlxsw_sp1_mr_tcam_region *tcam_region;

	tcam_region = mlxsw_sp1_mr_tcam_protocol_region(mr_tcam, key->proto);
	parman_item_remove(tcam_region->parman,
			   route->parman_prio, &route->parman_item);
}