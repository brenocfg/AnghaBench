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
struct request_queue {int /*<<< orphan*/ * softirq_done_fn; } ;
typedef  int /*<<< orphan*/  softirq_done_fn ;

/* Variables and functions */

void blk_queue_softirq_done(struct request_queue *q, softirq_done_fn *fn)
{
	q->softirq_done_fn = fn;
}