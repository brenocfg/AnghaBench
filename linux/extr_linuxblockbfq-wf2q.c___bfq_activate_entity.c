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
struct bfq_service_tree {unsigned long long vtime; int /*<<< orphan*/  wsum; int /*<<< orphan*/  idle; } ;
struct bfq_entity {unsigned long long finish; unsigned long long start; int on_st; scalar_t__ weight; int /*<<< orphan*/ * tree; } ;

/* Variables and functions */
 struct bfq_service_tree* bfq_entity_service_tree (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_get_entity (struct bfq_entity*) ; 
 scalar_t__ bfq_gt (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  bfq_idle_extract (struct bfq_service_tree*,struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_update_fin_time_enqueue (struct bfq_entity*,struct bfq_service_tree*,int) ; 

__attribute__((used)) static void __bfq_activate_entity(struct bfq_entity *entity,
				  bool non_blocking_wait_rq)
{
	struct bfq_service_tree *st = bfq_entity_service_tree(entity);
	bool backshifted = false;
	unsigned long long min_vstart;

	/* See comments on bfq_fqq_update_budg_for_activation */
	if (non_blocking_wait_rq && bfq_gt(st->vtime, entity->finish)) {
		backshifted = true;
		min_vstart = entity->finish;
	} else
		min_vstart = st->vtime;

	if (entity->tree == &st->idle) {
		/*
		 * Must be on the idle tree, bfq_idle_extract() will
		 * check for that.
		 */
		bfq_idle_extract(st, entity);
		entity->start = bfq_gt(min_vstart, entity->finish) ?
			min_vstart : entity->finish;
	} else {
		/*
		 * The finish time of the entity may be invalid, and
		 * it is in the past for sure, otherwise the queue
		 * would have been on the idle tree.
		 */
		entity->start = min_vstart;
		st->wsum += entity->weight;
		/*
		 * entity is about to be inserted into a service tree,
		 * and then set in service: get a reference to make
		 * sure entity does not disappear until it is no
		 * longer in service or scheduled for service.
		 */
		bfq_get_entity(entity);

		entity->on_st = true;
	}

#ifdef BFQ_GROUP_IOSCHED_ENABLED
	if (!bfq_entity_to_bfqq(entity)) { /* bfq_group */
		struct bfq_group *bfqg =
			container_of(entity, struct bfq_group, entity);

		bfq_weights_tree_add(bfqg->bfqd, entity,
				     &bfqd->group_weights_tree);
	}
#endif

	bfq_update_fin_time_enqueue(entity, st, backshifted);
}