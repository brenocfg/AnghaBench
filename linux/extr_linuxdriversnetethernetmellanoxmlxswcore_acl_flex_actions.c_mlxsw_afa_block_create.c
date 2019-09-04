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
struct mlxsw_afa_block {TYPE_2__* first_set; TYPE_2__* cur_set; struct mlxsw_afa* afa; int /*<<< orphan*/  resource_list; } ;
struct mlxsw_afa {TYPE_1__* ops; } ;
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* prev; } ;
struct TYPE_3__ {scalar_t__ dummy_first_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_afa_block*) ; 
 struct mlxsw_afa_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* mlxsw_afa_set_create (int) ; 
 int /*<<< orphan*/  mlxsw_afa_set_destroy (TYPE_2__*) ; 

struct mlxsw_afa_block *mlxsw_afa_block_create(struct mlxsw_afa *mlxsw_afa)
{
	struct mlxsw_afa_block *block;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (!block)
		return NULL;
	INIT_LIST_HEAD(&block->resource_list);
	block->afa = mlxsw_afa;

	/* At least one action set is always present, so just create it here */
	block->first_set = mlxsw_afa_set_create(true);
	if (!block->first_set)
		goto err_first_set_create;

	/* In case user instructs to have dummy first set, we leave it
	 * empty here and create another, real, set right away.
	 */
	if (mlxsw_afa->ops->dummy_first_set) {
		block->cur_set = mlxsw_afa_set_create(false);
		if (!block->cur_set)
			goto err_second_set_create;
		block->cur_set->prev = block->first_set;
		block->first_set->next = block->cur_set;
	} else {
		block->cur_set = block->first_set;
	}

	return block;

err_second_set_create:
	mlxsw_afa_set_destroy(block->first_set);
err_first_set_create:
	kfree(block);
	return NULL;
}