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
struct ppa_addr {int dummy; } ;
struct pblk_line_meta {int blk_per_line; scalar_t__ smeta_sec; } ;
struct pblk_line {scalar_t__ state; struct nvm_chk_meta* chks; int /*<<< orphan*/  blk_bitmap; } ;
struct pblk {TYPE_1__* luns; struct nvm_tgt_dev* dev; struct pblk_line_meta lm; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int state; scalar_t__ wp; } ;
struct TYPE_2__ {struct ppa_addr bppa; } ;

/* Variables and functions */
 int NVM_CHK_ST_CLOSED ; 
 int NVM_CHK_ST_OPEN ; 
 scalar_t__ PBLK_LINESTATE_BAD ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 size_t pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 

__attribute__((used)) static int pblk_line_was_written(struct pblk_line *line,
				 struct pblk *pblk)
{

	struct pblk_line_meta *lm = &pblk->lm;
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct nvm_chk_meta *chunk;
	struct ppa_addr bppa;
	int smeta_blk;

	if (line->state == PBLK_LINESTATE_BAD)
		return 0;

	smeta_blk = find_first_zero_bit(line->blk_bitmap, lm->blk_per_line);
	if (smeta_blk >= lm->blk_per_line)
		return 0;

	bppa = pblk->luns[smeta_blk].bppa;
	chunk = &line->chks[pblk_ppa_to_pos(geo, bppa)];

	if (chunk->state & NVM_CHK_ST_CLOSED ||
	    (chunk->state & NVM_CHK_ST_OPEN
	     && chunk->wp >= lm->smeta_sec))
		return 1;

	return 0;
}