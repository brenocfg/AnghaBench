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
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_rq {struct pblk* private; int /*<<< orphan*/  end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_CHUNK_RESET_START ; 
 int /*<<< orphan*/  PBLK_ERASE ; 
 struct nvm_rq* pblk_alloc_rqd (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int /*<<< orphan*/  pblk_end_io_erase ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_ppa_to_line_id (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_setup_e_rq (struct pblk*,struct nvm_rq*,struct ppa_addr) ; 
 int pblk_submit_io (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_chunk_reset (int /*<<< orphan*/ ,struct ppa_addr*,int /*<<< orphan*/ ) ; 

int pblk_blk_erase_async(struct pblk *pblk, struct ppa_addr ppa)
{
	struct nvm_rq *rqd;
	int err;

	rqd = pblk_alloc_rqd(pblk, PBLK_ERASE);

	pblk_setup_e_rq(pblk, rqd, ppa);

	rqd->end_io = pblk_end_io_erase;
	rqd->private = pblk;

	trace_pblk_chunk_reset(pblk_disk_name(pblk),
				&ppa, PBLK_CHUNK_RESET_START);

	/* The write thread schedules erases so that it minimizes disturbances
	 * with writes. Thus, there is no need to take the LUN semaphore.
	 */
	err = pblk_submit_io(pblk, rqd, NULL);
	if (err) {
		struct nvm_tgt_dev *dev = pblk->dev;
		struct nvm_geo *geo = &dev->geo;

		pblk_err(pblk, "could not async erase line:%d,blk:%d\n",
					pblk_ppa_to_line_id(ppa),
					pblk_ppa_to_pos(geo, ppa));
	}

	return err;
}