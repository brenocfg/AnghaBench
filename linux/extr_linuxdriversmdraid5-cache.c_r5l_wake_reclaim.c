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
struct r5l_log {unsigned long reclaim_target; int /*<<< orphan*/  reclaim_thread; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 

void r5l_wake_reclaim(struct r5l_log *log, sector_t space)
{
	unsigned long target;
	unsigned long new = (unsigned long)space; /* overflow in theory */

	if (!log)
		return;
	do {
		target = log->reclaim_target;
		if (new < target)
			return;
	} while (cmpxchg(&log->reclaim_target, target, new) != target);
	md_wakeup_thread(log->reclaim_thread);
}