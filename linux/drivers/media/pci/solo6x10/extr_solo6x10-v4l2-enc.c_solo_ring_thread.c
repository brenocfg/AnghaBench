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
struct solo_dev {int /*<<< orphan*/  ring_thread_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ERESTARTSYS ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  solo_handle_ring (struct solo_dev*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int solo_ring_thread(void *data)
{
	struct solo_dev *solo_dev = data;
	DECLARE_WAITQUEUE(wait, current);

	set_freezable();
	add_wait_queue(&solo_dev->ring_thread_wait, &wait);

	for (;;) {
		long timeout = schedule_timeout_interruptible(HZ);

		if (timeout == -ERESTARTSYS || kthread_should_stop())
			break;
		solo_handle_ring(solo_dev);
		try_to_freeze();
	}

	remove_wait_queue(&solo_dev->ring_thread_wait, &wait);

	return 0;
}