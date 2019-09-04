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
struct TYPE_2__ {int budget; } ;
struct bfq_queue {TYPE_1__ entity; int /*<<< orphan*/  bfqd; } ;

/* Variables and functions */
 int bfq_bfqq_budget_left (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_budget_timeout (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_wait_request (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (int /*<<< orphan*/ ,struct bfq_queue*,char*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static bool bfq_may_expire_for_budg_timeout(struct bfq_queue *bfqq)
{
	bfq_log_bfqq(bfqq->bfqd, bfqq,
		"may_budget_timeout: wait_request %d left %d timeout %d",
		bfq_bfqq_wait_request(bfqq),
			bfq_bfqq_budget_left(bfqq) >=  bfqq->entity.budget / 3,
		bfq_bfqq_budget_timeout(bfqq));

	return (!bfq_bfqq_wait_request(bfqq) ||
		bfq_bfqq_budget_left(bfqq) >=  bfqq->entity.budget / 3)
		&&
		bfq_bfqq_budget_timeout(bfqq);
}