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
struct TYPE_2__ {int /*<<< orphan*/  chk; } ;
struct ppa_addr {TYPE_1__ m; } ;
struct pblk_lun {struct ppa_addr bppa; } ;
struct pblk_line_meta {int blk_per_line; } ;
struct pblk_line {int /*<<< orphan*/  blk_bitmap; int /*<<< orphan*/  id; struct nvm_chk_meta* chks; } ;
struct pblk {struct pblk_lun* luns; struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int state; int type; int /*<<< orphan*/  wp; int /*<<< orphan*/  cnlb; int /*<<< orphan*/  slba; int /*<<< orphan*/  wi; } ;

/* Variables and functions */
 int NVM_CHK_ST_OFFLINE ; 
 int NVM_CHK_TP_SZ_SPEC ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct nvm_chk_meta* pblk_chunk_get_off (struct pblk*,struct nvm_chk_meta*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_pblk_chunk_state (int /*<<< orphan*/ ,struct ppa_addr*,int) ; 

__attribute__((used)) static int pblk_setup_line_meta_chk(struct pblk *pblk, struct pblk_line *line,
				   struct nvm_chk_meta *meta)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	int i, nr_bad_chks = 0;

	for (i = 0; i < lm->blk_per_line; i++) {
		struct pblk_lun *rlun = &pblk->luns[i];
		struct nvm_chk_meta *chunk;
		struct nvm_chk_meta *chunk_meta;
		struct ppa_addr ppa;
		int pos;

		ppa = rlun->bppa;
		pos = pblk_ppa_to_pos(geo, ppa);
		chunk = &line->chks[pos];

		ppa.m.chk = line->id;
		chunk_meta = pblk_chunk_get_off(pblk, meta, ppa);

		chunk->state = chunk_meta->state;
		chunk->type = chunk_meta->type;
		chunk->wi = chunk_meta->wi;
		chunk->slba = chunk_meta->slba;
		chunk->cnlb = chunk_meta->cnlb;
		chunk->wp = chunk_meta->wp;

		trace_pblk_chunk_state(pblk_disk_name(pblk), &ppa,
					chunk->state);

		if (chunk->type & NVM_CHK_TP_SZ_SPEC) {
			WARN_ONCE(1, "pblk: custom-sized chunks unsupported\n");
			continue;
		}

		if (!(chunk->state & NVM_CHK_ST_OFFLINE))
			continue;

		set_bit(pos, line->blk_bitmap);
		nr_bad_chks++;
	}

	return nr_bad_chks;
}