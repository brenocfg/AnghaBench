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
struct pblk_gc {int /*<<< orphan*/  pipeline_gc; } ;
struct pblk {struct pblk_gc gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  pblk_gc_read (struct pblk*) ; 
 int /*<<< orphan*/  pblk_info (struct pblk*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_gc_reader_ts(void *data)
{
	struct pblk *pblk = data;
	struct pblk_gc *gc = &pblk->gc;

	while (!kthread_should_stop()) {
		if (!pblk_gc_read(pblk))
			continue;
		set_current_state(TASK_INTERRUPTIBLE);
		io_schedule();
	}

#ifdef CONFIG_NVM_PBLK_DEBUG
	pblk_info(pblk, "flushing gc pipeline, %d lines left\n",
		atomic_read(&gc->pipeline_gc));
#endif

	do {
		if (!atomic_read(&gc->pipeline_gc))
			break;

		schedule();
	} while (1);

	return 0;
}