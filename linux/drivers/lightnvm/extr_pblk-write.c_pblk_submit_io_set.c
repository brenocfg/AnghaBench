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
struct pblk_line {int /*<<< orphan*/  erase_bitmap; int /*<<< orphan*/  left_eblks; } ;
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_rq {int dummy; } ;

/* Variables and functions */
 int NVM_IO_ERR ; 
 int NVM_IO_OK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ pblk_blk_erase_async (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 struct pblk_line* pblk_line_get_erase (struct pblk*) ; 
 int /*<<< orphan*/  pblk_ppa_empty (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_set_empty (struct ppa_addr*) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int pblk_setup_w_rq (struct pblk*,struct nvm_rq*,struct ppa_addr*) ; 
 struct pblk_line* pblk_should_submit_meta_io (struct pblk*,struct nvm_rq*) ; 
 int pblk_submit_io (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ *) ; 
 int pblk_submit_meta_io (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_submit_io_set(struct pblk *pblk, struct nvm_rq *rqd)
{
	struct ppa_addr erase_ppa;
	struct pblk_line *meta_line;
	int err;

	pblk_ppa_set_empty(&erase_ppa);

	/* Assign lbas to ppas and populate request structure */
	err = pblk_setup_w_rq(pblk, rqd, &erase_ppa);
	if (err) {
		pblk_err(pblk, "could not setup write request: %d\n", err);
		return NVM_IO_ERR;
	}

	meta_line = pblk_should_submit_meta_io(pblk, rqd);

	/* Submit data write for current data line */
	err = pblk_submit_io(pblk, rqd, NULL);
	if (err) {
		pblk_err(pblk, "data I/O submission failed: %d\n", err);
		return NVM_IO_ERR;
	}

	if (!pblk_ppa_empty(erase_ppa)) {
		/* Submit erase for next data line */
		if (pblk_blk_erase_async(pblk, erase_ppa)) {
			struct pblk_line *e_line = pblk_line_get_erase(pblk);
			struct nvm_tgt_dev *dev = pblk->dev;
			struct nvm_geo *geo = &dev->geo;
			int bit;

			atomic_inc(&e_line->left_eblks);
			bit = pblk_ppa_to_pos(geo, erase_ppa);
			WARN_ON(!test_and_clear_bit(bit, e_line->erase_bitmap));
		}
	}

	if (meta_line) {
		/* Submit metadata write for previous data line */
		err = pblk_submit_meta_io(pblk, meta_line);
		if (err) {
			pblk_err(pblk, "metadata I/O submission failed: %d",
					err);
			return NVM_IO_ERR;
		}
	}

	return NVM_IO_OK;
}