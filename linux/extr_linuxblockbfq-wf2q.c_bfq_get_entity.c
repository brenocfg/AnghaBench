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
struct bfq_queue {int /*<<< orphan*/  ref; int /*<<< orphan*/  bfqd; } ;
struct bfq_entity {int dummy; } ;

/* Variables and functions */
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (int /*<<< orphan*/ ,struct bfq_queue*,char*,struct bfq_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfq_get_entity(struct bfq_entity *entity)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	if (bfqq) {
		bfqq->ref++;
		bfq_log_bfqq(bfqq->bfqd, bfqq, "get_entity: %p %d",
			     bfqq, bfqq->ref);
	}
}