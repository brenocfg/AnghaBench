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
struct pblk_line {int /*<<< orphan*/  left_seblks; struct nvm_chk_meta* chks; } ;
struct pblk {int /*<<< orphan*/  inflight_io; struct pblk_line* lines; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_rq {int /*<<< orphan*/  ppa_addr; scalar_t__ error; } ;
struct nvm_chk_meta {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVM_CHK_ST_FREE ; 
 int /*<<< orphan*/  NVM_CHK_ST_OFFLINE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_mark_bb (struct pblk*,struct pblk_line*,int /*<<< orphan*/ ) ; 
 size_t pblk_ppa_to_line (int /*<<< orphan*/ ) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pblk_end_io_erase(struct pblk *pblk, struct nvm_rq *rqd)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct nvm_chk_meta *chunk;
	struct pblk_line *line;
	int pos;

	line = &pblk->lines[pblk_ppa_to_line(rqd->ppa_addr)];
	pos = pblk_ppa_to_pos(geo, rqd->ppa_addr);
	chunk = &line->chks[pos];

	atomic_dec(&line->left_seblks);

	if (rqd->error) {
		chunk->state = NVM_CHK_ST_OFFLINE;
		pblk_mark_bb(pblk, line, rqd->ppa_addr);
	} else {
		chunk->state = NVM_CHK_ST_FREE;
	}

	atomic_dec(&pblk->inflight_io);
}