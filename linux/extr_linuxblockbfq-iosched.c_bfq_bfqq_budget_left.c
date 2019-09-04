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
struct bfq_entity {int budget; int service; } ;
struct bfq_queue {struct bfq_entity entity; } ;

/* Variables and functions */

__attribute__((used)) static int bfq_bfqq_budget_left(struct bfq_queue *bfqq)
{
	struct bfq_entity *entity = &bfqq->entity;

	return entity->budget - entity->service;
}