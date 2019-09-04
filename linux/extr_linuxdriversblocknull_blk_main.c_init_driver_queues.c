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
struct nullb_queue {int dummy; } ;
struct nullb {int /*<<< orphan*/  nr_queues; struct nullb_queue* queues; TYPE_1__* dev; } ;
struct TYPE_2__ {int submit_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_init_queue (struct nullb*,struct nullb_queue*) ; 
 int setup_commands (struct nullb_queue*) ; 

__attribute__((used)) static int init_driver_queues(struct nullb *nullb)
{
	struct nullb_queue *nq;
	int i, ret = 0;

	for (i = 0; i < nullb->dev->submit_queues; i++) {
		nq = &nullb->queues[i];

		null_init_queue(nullb, nq);

		ret = setup_commands(nq);
		if (ret)
			return ret;
		nullb->nr_queues++;
	}
	return 0;
}