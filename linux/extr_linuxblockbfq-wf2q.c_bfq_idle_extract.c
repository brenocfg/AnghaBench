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
struct bfq_service_tree {int /*<<< orphan*/  idle; struct bfq_entity* last_idle; struct bfq_entity* first_idle; } ;
struct bfq_queue {int /*<<< orphan*/  bfqq_list; } ;
struct bfq_entity {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 void* bfq_entity_of (struct rb_node*) ; 
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_extract (int /*<<< orphan*/ *,struct bfq_entity*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_prev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfq_idle_extract(struct bfq_service_tree *st,
			     struct bfq_entity *entity)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	struct rb_node *next;

	if (entity == st->first_idle) {
		next = rb_next(&entity->rb_node);
		st->first_idle = bfq_entity_of(next);
	}

	if (entity == st->last_idle) {
		next = rb_prev(&entity->rb_node);
		st->last_idle = bfq_entity_of(next);
	}

	bfq_extract(&st->idle, entity);

	if (bfqq)
		list_del(&bfqq->bfqq_list);
}