#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  destructor; } ;
struct mlxsw_afa_counter {TYPE_3__ resource; int /*<<< orphan*/  counter_index; } ;
struct mlxsw_afa_block {TYPE_2__* afa; } ;
struct TYPE_5__ {int /*<<< orphan*/  ops_priv; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* counter_index_get ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_afa_counter* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_afa_counter*) ; 
 struct mlxsw_afa_counter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_counter_destructor ; 
 int /*<<< orphan*/  mlxsw_afa_resource_add (struct mlxsw_afa_block*,TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_afa_counter *
mlxsw_afa_counter_create(struct mlxsw_afa_block *block)
{
	struct mlxsw_afa_counter *counter;
	int err;

	counter = kzalloc(sizeof(*counter), GFP_KERNEL);
	if (!counter)
		return ERR_PTR(-ENOMEM);

	err = block->afa->ops->counter_index_get(block->afa->ops_priv,
						 &counter->counter_index);
	if (err)
		goto err_counter_index_get;
	counter->resource.destructor = mlxsw_afa_counter_destructor;
	mlxsw_afa_resource_add(block, &counter->resource);
	return counter;

err_counter_index_get:
	kfree(counter);
	return ERR_PTR(err);
}