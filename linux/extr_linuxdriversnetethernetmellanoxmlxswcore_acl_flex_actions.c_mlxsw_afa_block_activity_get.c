#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_afa_block {TYPE_2__* afa; } ;
struct TYPE_4__ {int /*<<< orphan*/  ops_priv; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* kvdl_set_activity_get ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_block_first_kvdl_index (struct mlxsw_afa_block*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int mlxsw_afa_block_activity_get(struct mlxsw_afa_block *block, bool *activity)
{
	u32 kvdl_index = mlxsw_afa_block_first_kvdl_index(block);

	return block->afa->ops->kvdl_set_activity_get(block->afa->ops_priv,
						      kvdl_index, activity);
}