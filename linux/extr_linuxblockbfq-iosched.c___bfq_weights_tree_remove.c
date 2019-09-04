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
struct rb_root {int dummy; } ;
struct bfq_entity {TYPE_1__* weight_counter; } ;
struct bfq_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ num_active; int /*<<< orphan*/  weights_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,struct rb_root*) ; 

void __bfq_weights_tree_remove(struct bfq_data *bfqd,
			       struct bfq_entity *entity,
			       struct rb_root *root)
{
	if (!entity->weight_counter)
		return;

	entity->weight_counter->num_active--;
	if (entity->weight_counter->num_active > 0)
		goto reset_entity_pointer;

	rb_erase(&entity->weight_counter->weights_node, root);
	kfree(entity->weight_counter);

reset_entity_pointer:
	entity->weight_counter = NULL;
}