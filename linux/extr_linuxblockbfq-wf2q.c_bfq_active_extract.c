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
struct rb_node {int dummy; } ;
struct bfq_service_tree {int /*<<< orphan*/  active; } ;
struct bfq_queue {int /*<<< orphan*/  bfqq_list; } ;
struct bfq_entity {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_extract (int /*<<< orphan*/ *,struct bfq_entity*) ; 
 struct rb_node* bfq_find_deepest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfq_update_active_tree (struct rb_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfq_active_extract(struct bfq_service_tree *st,
			       struct bfq_entity *entity)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	struct rb_node *node;
#ifdef CONFIG_BFQ_GROUP_IOSCHED
	struct bfq_sched_data *sd = NULL;
	struct bfq_group *bfqg = NULL;
	struct bfq_data *bfqd = NULL;
#endif

	node = bfq_find_deepest(&entity->rb_node);
	bfq_extract(&st->active, entity);

	if (node)
		bfq_update_active_tree(node);

#ifdef CONFIG_BFQ_GROUP_IOSCHED
	sd = entity->sched_data;
	bfqg = container_of(sd, struct bfq_group, sched_data);
	bfqd = (struct bfq_data *)bfqg->bfqd;
#endif
	if (bfqq)
		list_del(&bfqq->bfqq_list);
#ifdef CONFIG_BFQ_GROUP_IOSCHED
	if (bfqg != bfqd->root_group)
		bfqg->active_entities--;
#endif
}