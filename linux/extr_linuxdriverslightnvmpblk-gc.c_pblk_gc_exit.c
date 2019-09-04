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
struct pblk_gc {scalar_t__ gc_writer_ts; int /*<<< orphan*/  gc_line_reader_wq; int /*<<< orphan*/  gc_reader_wq; scalar_t__ gc_reader_ts; scalar_t__ gc_ts; scalar_t__ gc_active; int /*<<< orphan*/  gc_timer; scalar_t__ gc_enabled; } ;
struct pblk {struct pblk_gc gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 

void pblk_gc_exit(struct pblk *pblk, bool graceful)
{
	struct pblk_gc *gc = &pblk->gc;

	gc->gc_enabled = 0;
	del_timer_sync(&gc->gc_timer);
	gc->gc_active = 0;

	if (gc->gc_ts)
		kthread_stop(gc->gc_ts);

	if (gc->gc_reader_ts)
		kthread_stop(gc->gc_reader_ts);

	if (graceful) {
		flush_workqueue(gc->gc_reader_wq);
		flush_workqueue(gc->gc_line_reader_wq);
	}

	destroy_workqueue(gc->gc_reader_wq);
	destroy_workqueue(gc->gc_line_reader_wq);

	if (gc->gc_writer_ts)
		kthread_stop(gc->gc_writer_ts);
}