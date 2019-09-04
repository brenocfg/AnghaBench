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
struct mapped_device {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  md_in_flight (struct mapped_device*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 scalar_t__ signal_pending_state (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int dm_wait_for_completion(struct mapped_device *md, long task_state)
{
	int r = 0;
	DEFINE_WAIT(wait);

	while (1) {
		prepare_to_wait(&md->wait, &wait, task_state);

		if (!md_in_flight(md))
			break;

		if (signal_pending_state(task_state, current)) {
			r = -EINTR;
			break;
		}

		io_schedule();
	}
	finish_wait(&md->wait, &wait);

	return r;
}