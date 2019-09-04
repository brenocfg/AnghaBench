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
struct rb_root {int dummy; } ;
struct bfq_service_tree {unsigned int wsum; int /*<<< orphan*/  vtime; } ;
struct bfq_queue {scalar_t__ ioprio_class; scalar_t__ new_ioprio_class; int wr_coeff; int /*<<< orphan*/  ioprio; struct bfq_data* bfqd; } ;
struct bfq_entity {unsigned int weight; scalar_t__ new_weight; scalar_t__ orig_weight; int /*<<< orphan*/  start; scalar_t__ prio_changed; } ;
struct bfq_data {struct rb_root group_weights_tree; struct rb_root queue_weights_tree; } ;

/* Variables and functions */
 scalar_t__ BFQ_MAX_WEIGHT ; 
 scalar_t__ BFQ_MIN_WEIGHT ; 
 int /*<<< orphan*/  __bfq_weights_tree_remove (struct bfq_data*,struct bfq_entity*,struct rb_root*) ; 
 struct bfq_service_tree* bfq_entity_service_tree (struct bfq_entity*) ; 
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_weight_to_ioprio (scalar_t__) ; 
 int /*<<< orphan*/  bfq_weights_tree_add (struct bfq_data*,struct bfq_entity*,struct rb_root*) ; 
 int /*<<< orphan*/  pr_crit (char*,scalar_t__) ; 

struct bfq_service_tree *
__bfq_entity_update_weight_prio(struct bfq_service_tree *old_st,
				struct bfq_entity *entity,
				bool update_class_too)
{
	struct bfq_service_tree *new_st = old_st;

	if (entity->prio_changed) {
		struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
		unsigned int prev_weight, new_weight;
		struct bfq_data *bfqd = NULL;
		struct rb_root *root;
#ifdef CONFIG_BFQ_GROUP_IOSCHED
		struct bfq_sched_data *sd;
		struct bfq_group *bfqg;
#endif

		if (bfqq)
			bfqd = bfqq->bfqd;
#ifdef CONFIG_BFQ_GROUP_IOSCHED
		else {
			sd = entity->my_sched_data;
			bfqg = container_of(sd, struct bfq_group, sched_data);
			bfqd = (struct bfq_data *)bfqg->bfqd;
		}
#endif

		old_st->wsum -= entity->weight;

		if (entity->new_weight != entity->orig_weight) {
			if (entity->new_weight < BFQ_MIN_WEIGHT ||
			    entity->new_weight > BFQ_MAX_WEIGHT) {
				pr_crit("update_weight_prio: new_weight %d\n",
					entity->new_weight);
				if (entity->new_weight < BFQ_MIN_WEIGHT)
					entity->new_weight = BFQ_MIN_WEIGHT;
				else
					entity->new_weight = BFQ_MAX_WEIGHT;
			}
			entity->orig_weight = entity->new_weight;
			if (bfqq)
				bfqq->ioprio =
				  bfq_weight_to_ioprio(entity->orig_weight);
		}

		if (bfqq && update_class_too)
			bfqq->ioprio_class = bfqq->new_ioprio_class;

		/*
		 * Reset prio_changed only if the ioprio_class change
		 * is not pending any longer.
		 */
		if (!bfqq || bfqq->ioprio_class == bfqq->new_ioprio_class)
			entity->prio_changed = 0;

		/*
		 * NOTE: here we may be changing the weight too early,
		 * this will cause unfairness.  The correct approach
		 * would have required additional complexity to defer
		 * weight changes to the proper time instants (i.e.,
		 * when entity->finish <= old_st->vtime).
		 */
		new_st = bfq_entity_service_tree(entity);

		prev_weight = entity->weight;
		new_weight = entity->orig_weight *
			     (bfqq ? bfqq->wr_coeff : 1);
		/*
		 * If the weight of the entity changes, remove the entity
		 * from its old weight counter (if there is a counter
		 * associated with the entity), and add it to the counter
		 * associated with its new weight.
		 */
		if (prev_weight != new_weight) {
			root = bfqq ? &bfqd->queue_weights_tree :
				      &bfqd->group_weights_tree;
			__bfq_weights_tree_remove(bfqd, entity, root);
		}
		entity->weight = new_weight;
		/*
		 * Add the entity to its weights tree only if it is
		 * not associated with a weight-raised queue.
		 */
		if (prev_weight != new_weight &&
		    (bfqq ? bfqq->wr_coeff == 1 : 1))
			/* If we get here, root has been initialized. */
			bfq_weights_tree_add(bfqd, entity, root);

		new_st->wsum += entity->weight;

		if (new_st != old_st)
			entity->start = new_st->vtime;
	}

	return new_st;
}