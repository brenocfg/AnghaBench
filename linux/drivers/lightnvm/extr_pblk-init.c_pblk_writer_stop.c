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
struct pblk {scalar_t__ writer_ts; int /*<<< orphan*/  wtimer; int /*<<< orphan*/  rwb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  pblk_rb_read_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rb_sync_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pblk_writer_stop(struct pblk *pblk)
{
	/* The pipeline must be stopped and the write buffer emptied before the
	 * write thread is stopped
	 */
	WARN(pblk_rb_read_count(&pblk->rwb),
			"Stopping not fully persisted write buffer\n");

	WARN(pblk_rb_sync_count(&pblk->rwb),
			"Stopping not fully synced write buffer\n");

	del_timer_sync(&pblk->wtimer);
	if (pblk->writer_ts)
		kthread_stop(pblk->writer_ts);
}