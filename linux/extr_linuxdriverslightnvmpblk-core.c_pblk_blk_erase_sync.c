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
struct nvm_rq {int error; struct pblk* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_end_io_erase (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_ppa_to_line (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_setup_e_rq (struct pblk*,struct nvm_rq*,struct ppa_addr) ; 
 int pblk_submit_io_sync (struct pblk*,struct nvm_rq*) ; 

__attribute__((used)) static int pblk_blk_erase_sync(struct pblk *pblk, struct ppa_addr ppa)
{
	struct nvm_rq rqd;
	int ret = 0;

	memset(&rqd, 0, sizeof(struct nvm_rq));

	pblk_setup_e_rq(pblk, &rqd, ppa);

	/* The write thread schedules erases so that it minimizes disturbances
	 * with writes. Thus, there is no need to take the LUN semaphore.
	 */
	ret = pblk_submit_io_sync(pblk, &rqd);
	if (ret) {
		struct nvm_tgt_dev *dev = pblk->dev;
		struct nvm_geo *geo = &dev->geo;

		pblk_err(pblk, "could not sync erase line:%d,blk:%d\n",
					pblk_ppa_to_line(ppa),
					pblk_ppa_to_pos(geo, ppa));

		rqd.error = ret;
		goto out;
	}

out:
	rqd.private = pblk;
	__pblk_end_io_erase(pblk, &rqd);

	return ret;
}