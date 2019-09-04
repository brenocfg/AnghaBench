#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_kvdl {int /*<<< orphan*/  priv; TYPE_1__* kvdl_ops; } ;
struct mlxsw_sp {struct mlxsw_sp_kvdl* kvdl; } ;
typedef  enum mlxsw_sp_kvdl_entry_type { ____Placeholder_mlxsw_sp_kvdl_entry_type } mlxsw_sp_kvdl_entry_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int,unsigned int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int,unsigned int,int) ; 

void mlxsw_sp_kvdl_free(struct mlxsw_sp *mlxsw_sp,
			enum mlxsw_sp_kvdl_entry_type type,
			unsigned int entry_count, int entry_index)
{
	struct mlxsw_sp_kvdl *kvdl = mlxsw_sp->kvdl;

	kvdl->kvdl_ops->free(mlxsw_sp, kvdl->priv, type,
			     entry_count, entry_index);
}