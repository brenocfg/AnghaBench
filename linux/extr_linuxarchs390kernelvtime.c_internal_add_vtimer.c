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
struct vtimer_list {scalar_t__ expires; int /*<<< orphan*/  entry; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_sorted (struct vtimer_list*,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_timer_current ; 
 int /*<<< orphan*/  virt_timer_elapsed ; 
 int /*<<< orphan*/  virt_timer_list ; 

__attribute__((used)) static void internal_add_vtimer(struct vtimer_list *timer)
{
	if (list_empty(&virt_timer_list)) {
		/* First timer, just program it. */
		atomic64_set(&virt_timer_current, timer->expires);
		atomic64_set(&virt_timer_elapsed, 0);
		list_add(&timer->entry, &virt_timer_list);
	} else {
		/* Update timer against current base. */
		timer->expires += atomic64_read(&virt_timer_elapsed);
		if (likely((s64) timer->expires <
			   (s64) atomic64_read(&virt_timer_current)))
			/* The new timer expires before the current timer. */
			atomic64_set(&virt_timer_current, timer->expires);
		/* Insert new timer into the list. */
		list_add_sorted(timer, &virt_timer_list);
	}
}