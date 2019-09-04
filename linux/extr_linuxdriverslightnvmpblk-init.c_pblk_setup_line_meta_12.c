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
typedef  scalar_t__ u8 ;
struct pblk_lun {int /*<<< orphan*/  bppa; } ;
struct pblk_line_meta {int blk_per_line; } ;
struct pblk_line {size_t id; int /*<<< orphan*/  blk_bitmap; struct nvm_chk_meta* chks; } ;
struct pblk {struct pblk_lun* luns; struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int num_chk; int pln_mode; int /*<<< orphan*/  clba; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int state; int slba; scalar_t__ wp; int /*<<< orphan*/  cnlb; scalar_t__ wi; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ NVM_BLK_T_FREE ; 
 int NVM_CHK_ST_CLOSED ; 
 int NVM_CHK_ST_OFFLINE ; 
 int /*<<< orphan*/  NVM_CHK_TP_W_SEQ ; 
 int pblk_ppa_to_pos (struct nvm_geo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_setup_line_meta_12(struct pblk *pblk, struct pblk_line *line,
				   void *chunk_meta)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	int i, chk_per_lun, nr_bad_chks = 0;

	chk_per_lun = geo->num_chk * geo->pln_mode;

	for (i = 0; i < lm->blk_per_line; i++) {
		struct pblk_lun *rlun = &pblk->luns[i];
		struct nvm_chk_meta *chunk;
		int pos = pblk_ppa_to_pos(geo, rlun->bppa);
		u8 *lun_bb_meta = chunk_meta + pos * chk_per_lun;

		chunk = &line->chks[pos];

		/*
		 * In 1.2 spec. chunk state is not persisted by the device. Thus
		 * some of the values are reset each time pblk is instantiated,
		 * so we have to assume that the block is closed.
		 */
		if (lun_bb_meta[line->id] == NVM_BLK_T_FREE)
			chunk->state =  NVM_CHK_ST_CLOSED;
		else
			chunk->state = NVM_CHK_ST_OFFLINE;

		chunk->type = NVM_CHK_TP_W_SEQ;
		chunk->wi = 0;
		chunk->slba = -1;
		chunk->cnlb = geo->clba;
		chunk->wp = 0;

		if (!(chunk->state & NVM_CHK_ST_OFFLINE))
			continue;

		set_bit(pos, line->blk_bitmap);
		nr_bad_chks++;
	}

	return nr_bad_chks;
}