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
struct pblk {int /*<<< orphan*/  rl; int /*<<< orphan*/  rwb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_pipeline_flush (struct pblk*) ; 
 int /*<<< orphan*/  __pblk_pipeline_stop (struct pblk*) ; 
 int /*<<< orphan*/  pblk_debug (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_rb_sync_l2p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_writer_stop (struct pblk*) ; 

__attribute__((used)) static void pblk_tear_down(struct pblk *pblk, bool graceful)
{
	if (graceful)
		__pblk_pipeline_flush(pblk);
	__pblk_pipeline_stop(pblk);
	pblk_writer_stop(pblk);
	pblk_rb_sync_l2p(&pblk->rwb);
	pblk_rl_free(&pblk->rl);

	pblk_debug(pblk, "consistent tear down (graceful:%d)\n", graceful);
}