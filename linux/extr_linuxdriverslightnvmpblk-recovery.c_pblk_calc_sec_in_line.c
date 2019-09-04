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
struct pblk_line_meta {int sec_per_line; int smeta_sec; int* emeta_sec; int /*<<< orphan*/  blk_per_line; } ;
struct pblk_line {int /*<<< orphan*/  blk_bitmap; } ;
struct pblk {struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int clba; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_calc_sec_in_line(struct pblk *pblk, struct pblk_line *line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	int nr_bb = bitmap_weight(line->blk_bitmap, lm->blk_per_line);

	return lm->sec_per_line - lm->smeta_sec - lm->emeta_sec[0] -
				nr_bb * geo->clba;
}