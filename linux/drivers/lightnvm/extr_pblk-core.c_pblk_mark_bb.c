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
struct pblk_line {int /*<<< orphan*/  id; int /*<<< orphan*/  blk_bitmap; int /*<<< orphan*/  blk_in_line; } ;
struct pblk {int /*<<< orphan*/  bb_wq; int /*<<< orphan*/  erase_failed; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ version; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NVM_OCSSD_SPEC_20 ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct ppa_addr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_debug (struct pblk*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_gen_run_ws (struct pblk*,int /*<<< orphan*/ *,struct ppa_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_line_mark_bb ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_mark_bb(struct pblk *pblk, struct pblk_line *line,
			 struct ppa_addr ppa_addr)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct ppa_addr *ppa;
	int pos = pblk_ppa_to_pos(geo, ppa_addr);

	pblk_debug(pblk, "erase failed: line:%d, pos:%d\n", line->id, pos);
	atomic_long_inc(&pblk->erase_failed);

	atomic_dec(&line->blk_in_line);
	if (test_and_set_bit(pos, line->blk_bitmap))
		pblk_err(pblk, "attempted to erase bb: line:%d, pos:%d\n",
							line->id, pos);

	/* Not necessary to mark bad blocks on 2.0 spec. */
	if (geo->version == NVM_OCSSD_SPEC_20)
		return;

	ppa = kmalloc(sizeof(struct ppa_addr), GFP_ATOMIC);
	if (!ppa)
		return;

	*ppa = ppa_addr;
	pblk_gen_run_ws(pblk, NULL, ppa, pblk_line_mark_bb,
						GFP_ATOMIC, pblk->bb_wq);
}