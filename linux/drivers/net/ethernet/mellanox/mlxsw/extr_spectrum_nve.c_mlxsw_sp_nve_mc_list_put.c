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
struct mlxsw_sp_nve_mc_list {int /*<<< orphan*/  records_list; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_list_destroy (struct mlxsw_sp*,struct mlxsw_sp_nve_mc_list*) ; 

__attribute__((used)) static void
mlxsw_sp_nve_mc_list_put(struct mlxsw_sp *mlxsw_sp,
			 struct mlxsw_sp_nve_mc_list *mc_list)
{
	if (!list_empty(&mc_list->records_list))
		return;
	mlxsw_sp_nve_mc_list_destroy(mlxsw_sp, mc_list);
}