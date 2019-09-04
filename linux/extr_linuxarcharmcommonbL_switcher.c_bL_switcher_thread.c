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
struct sched_param {int sched_priority; } ;
struct bL_thread {int wanted_cluster; int /*<<< orphan*/  lock; int /*<<< orphan*/  (* completer ) (void*) ;void* completer_cookie; int /*<<< orphan*/  wq; int /*<<< orphan*/  started; } ;
typedef  int /*<<< orphan*/  (* bL_switch_completion_handler ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  bL_switch_to (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  sched_setscheduler_nocheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bL_switcher_thread(void *arg)
{
	struct bL_thread *t = arg;
	struct sched_param param = { .sched_priority = 1 };
	int cluster;
	bL_switch_completion_handler completer;
	void *completer_cookie;

	sched_setscheduler_nocheck(current, SCHED_FIFO, &param);
	complete(&t->started);

	do {
		if (signal_pending(current))
			flush_signals(current);
		wait_event_interruptible(t->wq,
				t->wanted_cluster != -1 ||
				kthread_should_stop());

		spin_lock(&t->lock);
		cluster = t->wanted_cluster;
		completer = t->completer;
		completer_cookie = t->completer_cookie;
		t->wanted_cluster = -1;
		t->completer = NULL;
		spin_unlock(&t->lock);

		if (cluster != -1) {
			bL_switch_to(cluster);

			if (completer)
				completer(completer_cookie);
		}
	} while (!kthread_should_stop());

	return 0;
}