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
struct ppa_addr {int dummy; } ;
struct pblk {int dummy; } ;
struct nvm_rq {struct pblk* private; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_CHUNK_RESET_START ; 
 int /*<<< orphan*/  __pblk_end_io_erase (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int /*<<< orphan*/  pblk_setup_e_rq (struct pblk*,struct nvm_rq*,struct ppa_addr) ; 
 int pblk_submit_io_sync (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_chunk_reset (int /*<<< orphan*/ ,struct ppa_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_blk_erase_sync(struct pblk *pblk, struct ppa_addr ppa)
{
	struct nvm_rq rqd = {NULL};
	int ret;

	trace_pblk_chunk_reset(pblk_disk_name(pblk), &ppa,
				PBLK_CHUNK_RESET_START);

	pblk_setup_e_rq(pblk, &rqd, ppa);

	/* The write thread schedules erases so that it minimizes disturbances
	 * with writes. Thus, there is no need to take the LUN semaphore.
	 */
	ret = pblk_submit_io_sync(pblk, &rqd, NULL);
	rqd.private = pblk;
	__pblk_end_io_erase(pblk, &rqd);

	return ret;
}