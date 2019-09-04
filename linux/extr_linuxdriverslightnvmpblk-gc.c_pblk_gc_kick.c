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
struct pblk_gc {int /*<<< orphan*/  gc_timer; int /*<<< orphan*/  gc_ts; scalar_t__ gc_enabled; } ;
struct pblk {struct pblk_gc gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC_TIME_MSECS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_gc_reader_kick (struct pblk_gc*) ; 
 int /*<<< orphan*/  pblk_gc_writer_kick (struct pblk_gc*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_gc_kick(struct pblk *pblk)
{
	struct pblk_gc *gc = &pblk->gc;

	pblk_gc_writer_kick(gc);
	pblk_gc_reader_kick(gc);

	/* If we're shutting down GC, let's not start it up again */
	if (gc->gc_enabled) {
		wake_up_process(gc->gc_ts);
		mod_timer(&gc->gc_timer,
			  jiffies + msecs_to_jiffies(GC_TIME_MSECS));
	}
}