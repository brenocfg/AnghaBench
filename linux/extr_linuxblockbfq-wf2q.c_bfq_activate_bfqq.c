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
struct bfq_entity {int dummy; } ;
struct bfq_queue {struct bfq_entity entity; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_activate_requeue_entity (struct bfq_entity*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bfq_bfqq_non_blocking_wait_rq (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_non_blocking_wait_rq (struct bfq_queue*) ; 

void bfq_activate_bfqq(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{
	struct bfq_entity *entity = &bfqq->entity;

	bfq_activate_requeue_entity(entity, bfq_bfqq_non_blocking_wait_rq(bfqq),
				    false, false);
	bfq_clear_bfqq_non_blocking_wait_rq(bfqq);
}