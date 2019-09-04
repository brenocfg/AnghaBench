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
struct throtl_service_queue {int /*<<< orphan*/  first_pending_disptime; int /*<<< orphan*/  nr_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  throtl_schedule_pending_timer (struct throtl_service_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_min_dispatch_time (struct throtl_service_queue*) ; 

__attribute__((used)) static bool throtl_schedule_next_dispatch(struct throtl_service_queue *sq,
					  bool force)
{
	/* any pending children left? */
	if (!sq->nr_pending)
		return true;

	update_min_dispatch_time(sq);

	/* is the next dispatch time in the future? */
	if (force || time_after(sq->first_pending_disptime, jiffies)) {
		throtl_schedule_pending_timer(sq, sq->first_pending_disptime);
		return true;
	}

	/* tell the caller to continue dispatching */
	return false;
}