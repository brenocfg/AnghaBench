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
struct pblk_lun {int /*<<< orphan*/  wr_sem; } ;
struct pblk {struct pblk_lun* luns; } ;

/* Variables and functions */
 int EINTR ; 
 int ETIME ; 
 int down_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 

__attribute__((used)) static void __pblk_down_chunk(struct pblk *pblk, int pos)
{
	struct pblk_lun *rlun = &pblk->luns[pos];
	int ret;

	/*
	 * Only send one inflight I/O per LUN. Since we map at a page
	 * granurality, all ppas in the I/O will map to the same LUN
	 */

	ret = down_timeout(&rlun->wr_sem, msecs_to_jiffies(30000));
	if (ret == -ETIME || ret == -EINTR)
		pblk_err(pblk, "taking lun semaphore timed out: err %d\n",
				-ret);
}