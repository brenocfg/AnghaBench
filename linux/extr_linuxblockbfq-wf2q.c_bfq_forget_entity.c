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
struct bfq_service_tree {int /*<<< orphan*/  wsum; } ;
struct bfq_queue {int dummy; } ;
struct bfq_entity {int on_st; scalar_t__ weight; } ;

/* Variables and functions */
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_put_queue (struct bfq_queue*) ; 

__attribute__((used)) static void bfq_forget_entity(struct bfq_service_tree *st,
			      struct bfq_entity *entity,
			      bool is_in_service)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->on_st = false;
	st->wsum -= entity->weight;
	if (bfqq && !is_in_service)
		bfq_put_queue(bfqq);
}