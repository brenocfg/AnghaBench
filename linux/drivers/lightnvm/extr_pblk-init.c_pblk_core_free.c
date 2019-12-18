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
struct pblk {int /*<<< orphan*/  pad_dist; int /*<<< orphan*/  w_rq_pool; int /*<<< orphan*/  e_rq_pool; int /*<<< orphan*/  r_rq_pool; int /*<<< orphan*/  rec_pool; int /*<<< orphan*/  gen_ws_pool; int /*<<< orphan*/  page_bio_pool; scalar_t__ bb_wq; scalar_t__ r_end_wq; scalar_t__ close_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_put_global_caches () ; 

__attribute__((used)) static void pblk_core_free(struct pblk *pblk)
{
	if (pblk->close_wq)
		destroy_workqueue(pblk->close_wq);

	if (pblk->r_end_wq)
		destroy_workqueue(pblk->r_end_wq);

	if (pblk->bb_wq)
		destroy_workqueue(pblk->bb_wq);

	mempool_exit(&pblk->page_bio_pool);
	mempool_exit(&pblk->gen_ws_pool);
	mempool_exit(&pblk->rec_pool);
	mempool_exit(&pblk->r_rq_pool);
	mempool_exit(&pblk->e_rq_pool);
	mempool_exit(&pblk->w_rq_pool);

	pblk_put_global_caches();
	kfree(pblk->pad_dist);
}