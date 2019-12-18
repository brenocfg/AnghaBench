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
struct mlxsw_sp_flood_table {int dummy; } ;
struct mlxsw_sp_fid_family {int nr_flood_tables; struct mlxsw_sp_flood_table* flood_tables; } ;

/* Variables and functions */
 int mlxsw_sp_fid_flood_table_init (struct mlxsw_sp_fid_family*,struct mlxsw_sp_flood_table const*) ; 

__attribute__((used)) static int
mlxsw_sp_fid_flood_tables_init(struct mlxsw_sp_fid_family *fid_family)
{
	int i;

	for (i = 0; i < fid_family->nr_flood_tables; i++) {
		const struct mlxsw_sp_flood_table *flood_table;
		int err;

		flood_table = &fid_family->flood_tables[i];
		err = mlxsw_sp_fid_flood_table_init(fid_family, flood_table);
		if (err)
			return err;
	}

	return 0;
}