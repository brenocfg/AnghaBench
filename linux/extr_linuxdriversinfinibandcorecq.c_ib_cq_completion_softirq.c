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
struct ib_cq {int /*<<< orphan*/  iop; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_poll_sched (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_cq_completion_softirq(struct ib_cq *cq, void *private)
{
	irq_poll_sched(&cq->iop);
}