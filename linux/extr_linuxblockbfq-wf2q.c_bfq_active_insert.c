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
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct bfq_service_tree {int /*<<< orphan*/  active; } ;
struct bfq_queue {TYPE_1__* bfqd; int /*<<< orphan*/  bfqq_list; } ;
struct bfq_entity {struct rb_node rb_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  active_list; } ;

/* Variables and functions */
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_insert (int /*<<< orphan*/ *,struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_update_active_tree (struct rb_node*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfq_active_insert(struct bfq_service_tree *st,
			      struct bfq_entity *entity)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	struct rb_node *node = &entity->rb_node;
#ifdef CONFIG_BFQ_GROUP_IOSCHED
	struct bfq_sched_data *sd = NULL;
	struct bfq_group *bfqg = NULL;
	struct bfq_data *bfqd = NULL;
#endif

	bfq_insert(&st->active, entity);

	if (node->rb_left)
		node = node->rb_left;
	else if (node->rb_right)
		node = node->rb_right;

	bfq_update_active_tree(node);

#ifdef CONFIG_BFQ_GROUP_IOSCHED
	sd = entity->sched_data;
	bfqg = container_of(sd, struct bfq_group, sched_data);
	bfqd = (struct bfq_data *)bfqg->bfqd;
#endif
	if (bfqq)
		list_add(&bfqq->bfqq_list, &bfqq->bfqd->active_list);
#ifdef CONFIG_BFQ_GROUP_IOSCHED
	if (bfqg != bfqd->root_group)
		bfqg->active_entities++;
#endif
}