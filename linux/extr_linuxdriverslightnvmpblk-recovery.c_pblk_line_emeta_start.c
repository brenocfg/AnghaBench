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
typedef  int /*<<< orphan*/  u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_line_meta {unsigned int* emeta_sec; int /*<<< orphan*/  sec_per_line; } ;
struct pblk_line {int /*<<< orphan*/  blk_bitmap; int /*<<< orphan*/  id; } ;
struct pblk {struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 struct ppa_addr addr_to_gen_ppa (struct pblk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 pblk_line_emeta_start(struct pblk *pblk, struct pblk_line *line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	unsigned int emeta_secs;
	u64 emeta_start;
	struct ppa_addr ppa;
	int pos;

	emeta_secs = lm->emeta_sec[0];
	emeta_start = lm->sec_per_line;

	while (emeta_secs) {
		emeta_start--;
		ppa = addr_to_gen_ppa(pblk, emeta_start, line->id);
		pos = pblk_ppa_to_pos(geo, ppa);
		if (!test_bit(pos, line->blk_bitmap))
			emeta_secs--;
	}

	return emeta_start;
}