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
struct bfq_data {struct bfq_queue* in_service_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_activate_requeue_entity (struct bfq_entity*,int,int,int) ; 

void bfq_requeue_bfqq(struct bfq_data *bfqd, struct bfq_queue *bfqq,
		      bool expiration)
{
	struct bfq_entity *entity = &bfqq->entity;

	bfq_activate_requeue_entity(entity, false,
				    bfqq == bfqd->in_service_queue, expiration);
}