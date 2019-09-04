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
struct request_queue {int /*<<< orphan*/  limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_stack_limits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blk_queue_stack_limits(struct request_queue *t, struct request_queue *b)
{
	blk_stack_limits(&t->limits, &b->limits, 0);
}