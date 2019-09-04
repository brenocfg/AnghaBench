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
struct igt_wakeup {int /*<<< orphan*/  flags; int /*<<< orphan*/  set; int /*<<< orphan*/  wq; int /*<<< orphan*/  ready; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDLE ; 
 int /*<<< orphan*/  STOP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ready ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool wait_for_ready(struct igt_wakeup *w)
{
	DEFINE_WAIT(ready);

	set_bit(IDLE, &w->flags);
	if (atomic_dec_and_test(w->done))
		wake_up_var(w->done);

	if (test_bit(STOP, &w->flags))
		goto out;

	for (;;) {
		prepare_to_wait(w->wq, &ready, TASK_INTERRUPTIBLE);
		if (atomic_read(w->ready) == 0)
			break;

		schedule();
	}
	finish_wait(w->wq, &ready);

out:
	clear_bit(IDLE, &w->flags);
	if (atomic_dec_and_test(w->set))
		wake_up_var(w->set);

	return !test_bit(STOP, &w->flags);
}