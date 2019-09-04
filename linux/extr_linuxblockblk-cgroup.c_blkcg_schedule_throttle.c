#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct TYPE_3__ {int flags; int use_memdelay; struct request_queue* throttle_queue; } ;

/* Variables and functions */
 int PF_KTHREAD ; 
 int /*<<< orphan*/  blk_get_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  set_notify_resume (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

void blkcg_schedule_throttle(struct request_queue *q, bool use_memdelay)
{
	if (unlikely(current->flags & PF_KTHREAD))
		return;

	if (!blk_get_queue(q))
		return;

	if (current->throttle_queue)
		blk_put_queue(current->throttle_queue);
	current->throttle_queue = q;
	if (use_memdelay)
		current->use_memdelay = use_memdelay;
	set_notify_resume(current);
}