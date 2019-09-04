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
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  pblk_gc_write (struct pblk*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_gc_writer_ts(void *data)
{
	struct pblk *pblk = data;

	while (!kthread_should_stop()) {
		if (!pblk_gc_write(pblk))
			continue;
		set_current_state(TASK_INTERRUPTIBLE);
		io_schedule();
	}

	return 0;
}