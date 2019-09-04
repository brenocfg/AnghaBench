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
typedef  int u64 ;
struct pblk_line_meta {int blk_per_line; } ;
struct pblk_line {int /*<<< orphan*/  blk_bitmap; } ;
struct pblk {struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int ws_opt; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 

u64 pblk_line_smeta_start(struct pblk *pblk, struct pblk_line *line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	int bit;

	/* This usually only happens on bad lines */
	bit = find_first_zero_bit(line->blk_bitmap, lm->blk_per_line);
	if (bit >= lm->blk_per_line)
		return -1;

	return bit * geo->ws_opt;
}