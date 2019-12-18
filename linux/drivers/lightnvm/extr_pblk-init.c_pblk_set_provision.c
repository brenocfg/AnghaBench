#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pblk_line_mgmt {int nr_free_lines; } ;
struct pblk_line_meta {int smeta_sec; int* emeta_sec; } ;
struct TYPE_2__ {int total_blocks; int /*<<< orphan*/  free_user_blocks; int /*<<< orphan*/  free_blocks; } ;
struct pblk {scalar_t__ op; int op_blks; int min_write_pgs; int min_write_pgs_data; int capacity; TYPE_1__ rl; struct pblk_line_meta lm; struct pblk_line_mgmt l_mg; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ op; int clba; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
typedef  int sector_t ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINTR ; 
 scalar_t__ NVM_TARGET_DEFAULT_OP ; 
 scalar_t__ PBLK_DEFAULT_OP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 int pblk_get_min_chks (struct pblk*) ; 
 int /*<<< orphan*/  pblk_info (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  sector_div (int,int) ; 

__attribute__((used)) static int pblk_set_provision(struct pblk *pblk, int nr_free_chks)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line_meta *lm = &pblk->lm;
	struct nvm_geo *geo = &dev->geo;
	sector_t provisioned;
	int sec_meta, blk_meta, clba;
	int minimum;

	if (geo->op == NVM_TARGET_DEFAULT_OP)
		pblk->op = PBLK_DEFAULT_OP;
	else
		pblk->op = geo->op;

	minimum = pblk_get_min_chks(pblk);
	provisioned = nr_free_chks;
	provisioned *= (100 - pblk->op);
	sector_div(provisioned, 100);

	if ((nr_free_chks - provisioned) < minimum) {
		if (geo->op != NVM_TARGET_DEFAULT_OP) {
			pblk_err(pblk, "OP too small to create a sane instance\n");
			return -EINTR;
		}

		/* If the user did not specify an OP value, and PBLK_DEFAULT_OP
		 * is not enough, calculate and set sane value
		 */

		provisioned = nr_free_chks - minimum;
		pblk->op =  (100 * minimum) / nr_free_chks;
		pblk_info(pblk, "Default OP insufficient, adjusting OP to %d\n",
				pblk->op);
	}

	pblk->op_blks = nr_free_chks - provisioned;

	/* Internally pblk manages all free blocks, but all calculations based
	 * on user capacity consider only provisioned blocks
	 */
	pblk->rl.total_blocks = nr_free_chks;

	/* Consider sectors used for metadata */
	sec_meta = (lm->smeta_sec + lm->emeta_sec[0]) * l_mg->nr_free_lines;
	blk_meta = DIV_ROUND_UP(sec_meta, geo->clba);

	clba = (geo->clba / pblk->min_write_pgs) * pblk->min_write_pgs_data;
	pblk->capacity = (provisioned - blk_meta) * clba;

	atomic_set(&pblk->rl.free_blocks, nr_free_chks);
	atomic_set(&pblk->rl.free_user_blocks, nr_free_chks);

	return 0;
}