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
struct mlxsw_sp1_kvdl {struct mlxsw_sp1_kvdl_part** parts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 struct mlxsw_sp1_kvdl_part* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MLXSW_SP1_KVDL_PARTS_INFO_LEN ; 

__attribute__((used)) static struct mlxsw_sp1_kvdl_part *
mlxsw_sp1_kvdl_alloc_size_part(struct mlxsw_sp1_kvdl *kvdl,
			       unsigned int alloc_size)
{
	struct mlxsw_sp1_kvdl_part *part, *min_part = NULL;
	int i;

	for (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++) {
		part = kvdl->parts[i];
		if (alloc_size <= part->info.alloc_size &&
		    (!min_part ||
		     part->info.alloc_size <= min_part->info.alloc_size))
			min_part = part;
	}

	return min_part ?: ERR_PTR(-ENOBUFS);
}