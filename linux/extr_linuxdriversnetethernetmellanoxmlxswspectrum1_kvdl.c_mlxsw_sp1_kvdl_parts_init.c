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
struct mlxsw_sp1_kvdl_part_info {int dummy; } ;
struct mlxsw_sp1_kvdl_part {int dummy; } ;
struct mlxsw_sp1_kvdl {struct mlxsw_sp1_kvdl_part** parts; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp1_kvdl_part*) ; 
 int MLXSW_SP1_KVDL_PARTS_INFO_LEN ; 
 int PTR_ERR (struct mlxsw_sp1_kvdl_part*) ; 
 int /*<<< orphan*/  mlxsw_sp1_kvdl_part_fini (struct mlxsw_sp1_kvdl_part*) ; 
 struct mlxsw_sp1_kvdl_part* mlxsw_sp1_kvdl_part_init (struct mlxsw_sp*,struct mlxsw_sp1_kvdl_part_info const*,struct mlxsw_sp1_kvdl_part*) ; 
 struct mlxsw_sp1_kvdl_part_info* mlxsw_sp1_kvdl_parts_info ; 

__attribute__((used)) static int mlxsw_sp1_kvdl_parts_init(struct mlxsw_sp *mlxsw_sp,
				     struct mlxsw_sp1_kvdl *kvdl)
{
	const struct mlxsw_sp1_kvdl_part_info *info;
	struct mlxsw_sp1_kvdl_part *part_prev = NULL;
	int err, i;

	for (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++) {
		info = &mlxsw_sp1_kvdl_parts_info[i];
		kvdl->parts[i] = mlxsw_sp1_kvdl_part_init(mlxsw_sp, info,
							  part_prev);
		if (IS_ERR(kvdl->parts[i])) {
			err = PTR_ERR(kvdl->parts[i]);
			goto err_kvdl_part_init;
		}
		part_prev = kvdl->parts[i];
	}
	return 0;

err_kvdl_part_init:
	for (i--; i >= 0; i--)
		mlxsw_sp1_kvdl_part_fini(kvdl->parts[i]);
	return err;
}