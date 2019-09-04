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
struct rq_wb {struct rq_wait* rq_wait; } ;
struct rq_wait {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int WBT_NUM_RWQ ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 scalar_t__ wq_has_sleeper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rwb_wake_all(struct rq_wb *rwb)
{
	int i;

	for (i = 0; i < WBT_NUM_RWQ; i++) {
		struct rq_wait *rqw = &rwb->rq_wait[i];

		if (wq_has_sleeper(&rqw->wait))
			wake_up_all(&rqw->wait);
	}
}