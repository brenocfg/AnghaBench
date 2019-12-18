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
struct pblk_line_mgmt {int /*<<< orphan*/  free_lock; } ;
struct pblk {scalar_t__ state; int /*<<< orphan*/  bb_wq; struct pblk_line_mgmt l_mg; } ;

/* Variables and functions */
 scalar_t__ PBLK_STATE_RECOVERING ; 
 scalar_t__ PBLK_STATE_STOPPED ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_flush_writer (struct pblk*) ; 
 int /*<<< orphan*/  pblk_line_close_meta_sync (struct pblk*) ; 
 int pblk_recov_pad (struct pblk*) ; 
 int /*<<< orphan*/  pblk_wait_for_meta (struct pblk*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_state (int /*<<< orphan*/ ,scalar_t__) ; 

void __pblk_pipeline_flush(struct pblk *pblk)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	int ret;

	spin_lock(&l_mg->free_lock);
	if (pblk->state == PBLK_STATE_RECOVERING ||
					pblk->state == PBLK_STATE_STOPPED) {
		spin_unlock(&l_mg->free_lock);
		return;
	}
	pblk->state = PBLK_STATE_RECOVERING;
	trace_pblk_state(pblk_disk_name(pblk), pblk->state);
	spin_unlock(&l_mg->free_lock);

	pblk_flush_writer(pblk);
	pblk_wait_for_meta(pblk);

	ret = pblk_recov_pad(pblk);
	if (ret) {
		pblk_err(pblk, "could not close data on teardown(%d)\n", ret);
		return;
	}

	flush_workqueue(pblk->bb_wq);
	pblk_line_close_meta_sync(pblk);
}