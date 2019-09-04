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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_mr_tcam_erif_list {int dummy; } ;
struct mlxsw_sp_mr_route_info {int erif_num; int /*<<< orphan*/ * erif_indices; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_mr_erif_list_add (struct mlxsw_sp*,struct mlxsw_sp_mr_tcam_erif_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_mr_tcam_erif_populate(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_mr_tcam_erif_list *erif_list,
			       struct mlxsw_sp_mr_route_info *route_info)
{
	int err;
	int i;

	for (i = 0; i < route_info->erif_num; i++) {
		u16 erif_index = route_info->erif_indices[i];

		err = mlxsw_sp_mr_erif_list_add(mlxsw_sp, erif_list,
						erif_index);
		if (err)
			return err;
	}
	return 0;
}