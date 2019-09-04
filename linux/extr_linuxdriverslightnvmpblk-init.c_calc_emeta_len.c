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
typedef  int /*<<< orphan*/  u32 ;
struct wa_counters {int dummy; } ;
struct pblk_line_mgmt {int nr_lines; } ;
struct pblk_line_meta {int* emeta_sec; int blk_bitmap_len; int* emeta_len; int dsec_per_line; int sec_per_line; int vsc_list_len; } ;
struct pblk {struct nvm_tgt_dev* dev; struct pblk_line_mgmt l_mg; struct pblk_line_meta lm; } ;
struct nvm_geo {int csecs; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct line_emeta {int dummy; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static unsigned int calc_emeta_len(struct pblk *pblk)
{
	struct pblk_line_meta *lm = &pblk->lm;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;

	/* Round to sector size so that lba_list starts on its own sector */
	lm->emeta_sec[1] = DIV_ROUND_UP(
			sizeof(struct line_emeta) + lm->blk_bitmap_len +
			sizeof(struct wa_counters), geo->csecs);
	lm->emeta_len[1] = lm->emeta_sec[1] * geo->csecs;

	/* Round to sector size so that vsc_list starts on its own sector */
	lm->dsec_per_line = lm->sec_per_line - lm->emeta_sec[0];
	lm->emeta_sec[2] = DIV_ROUND_UP(lm->dsec_per_line * sizeof(u64),
			geo->csecs);
	lm->emeta_len[2] = lm->emeta_sec[2] * geo->csecs;

	lm->emeta_sec[3] = DIV_ROUND_UP(l_mg->nr_lines * sizeof(u32),
			geo->csecs);
	lm->emeta_len[3] = lm->emeta_sec[3] * geo->csecs;

	lm->vsc_list_len = l_mg->nr_lines * sizeof(u32);

	return (lm->emeta_len[1] + lm->emeta_len[2] + lm->emeta_len[3]);
}