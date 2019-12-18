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
struct ddcb_queue {int ddcb_max; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int queue_enqueued_ddcbs (struct ddcb_queue*) ; 

__attribute__((used)) static int queue_free_ddcbs(struct ddcb_queue *queue)
{
	int free_ddcbs = queue->ddcb_max - queue_enqueued_ddcbs(queue) - 1;

	if (WARN_ON_ONCE(free_ddcbs < 0)) { /* must never ever happen! */
		return 0;
	}
	return free_ddcbs;
}