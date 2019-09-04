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
struct mlxsw_sp1_mr_tcam_region {int /*<<< orphan*/  parman; int /*<<< orphan*/ * parman_prios; } ;

/* Variables and functions */
 int MLXSW_SP_MR_ROUTE_PRIO_MAX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp1_mr_tcam_region_free (struct mlxsw_sp1_mr_tcam_region*) ; 
 int /*<<< orphan*/  parman_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parman_prio_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp1_mr_tcam_region_fini(struct mlxsw_sp1_mr_tcam_region *mr_tcam_region)
{
	int i;

	for (i = 0; i < MLXSW_SP_MR_ROUTE_PRIO_MAX + 1; i++)
		parman_prio_fini(&mr_tcam_region->parman_prios[i]);
	kfree(mr_tcam_region->parman_prios);
	parman_destroy(mr_tcam_region->parman);
	mlxsw_sp1_mr_tcam_region_free(mr_tcam_region);
}