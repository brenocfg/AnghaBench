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
struct mlxsw_sp2_kvdl_part {int dummy; } ;
struct mlxsw_sp2_kvdl {struct mlxsw_sp2_kvdl_part** parts; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_kvdl_entry_type { ____Placeholder_mlxsw_sp_kvdl_entry_type } mlxsw_sp_kvdl_entry_type ;

/* Variables and functions */
 void mlxsw_sp2_kvdl_part_free (struct mlxsw_sp*,struct mlxsw_sp2_kvdl_part*,unsigned int,int) ; 
 unsigned int mlxsw_sp_kvdl_entry_size (int) ; 

__attribute__((used)) static void mlxsw_sp2_kvdl_free(struct mlxsw_sp *mlxsw_sp, void *priv,
				enum mlxsw_sp_kvdl_entry_type type,
				unsigned int entry_count,
				int entry_index)
{
	unsigned int size = entry_count * mlxsw_sp_kvdl_entry_size(type);
	struct mlxsw_sp2_kvdl *kvdl = priv;
	struct mlxsw_sp2_kvdl_part *part = kvdl->parts[type];

	return mlxsw_sp2_kvdl_part_free(mlxsw_sp, part, size, entry_index);
}