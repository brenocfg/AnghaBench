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
struct TYPE_2__ {unsigned int alloc_size; } ;
struct mlxsw_sp1_kvdl_part {TYPE_1__ info; } ;
struct mlxsw_sp1_kvdl {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_kvdl_entry_type { ____Placeholder_mlxsw_sp_kvdl_entry_type } mlxsw_sp_kvdl_entry_type ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp1_kvdl_part*) ; 
 int PTR_ERR (struct mlxsw_sp1_kvdl_part*) ; 
 struct mlxsw_sp1_kvdl_part* mlxsw_sp1_kvdl_alloc_size_part (struct mlxsw_sp1_kvdl*,unsigned int) ; 

__attribute__((used)) static int mlxsw_sp1_kvdl_alloc_size_query(struct mlxsw_sp *mlxsw_sp,
					   void *priv,
					   enum mlxsw_sp_kvdl_entry_type type,
					   unsigned int entry_count,
					   unsigned int *p_alloc_size)
{
	struct mlxsw_sp1_kvdl *kvdl = priv;
	struct mlxsw_sp1_kvdl_part *part;

	part = mlxsw_sp1_kvdl_alloc_size_part(kvdl, entry_count);
	if (IS_ERR(part))
		return PTR_ERR(part);

	*p_alloc_size = part->info.alloc_size;

	return 0;
}