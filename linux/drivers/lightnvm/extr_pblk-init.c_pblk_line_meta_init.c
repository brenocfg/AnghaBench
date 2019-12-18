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
struct pblk_line_meta {int sec_per_line; int blk_per_line; int blk_bitmap_len; int sec_bitmap_len; int lun_bitmap_len; int mid_thrs; int high_thrs; int meta_distance; int smeta_sec; int smeta_len; int* emeta_sec; int* emeta_len; int emeta_bb; int min_blk_line; } ;
struct pblk {int min_write_pgs; struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int clba; int all_luns; int ws_opt; int csecs; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct line_smeta {int dummy; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 unsigned int calc_emeta_len (struct pblk*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 

__attribute__((used)) static int pblk_line_meta_init(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	unsigned int smeta_len, emeta_len;
	int i;

	lm->sec_per_line = geo->clba * geo->all_luns;
	lm->blk_per_line = geo->all_luns;
	lm->blk_bitmap_len = BITS_TO_LONGS(geo->all_luns) * sizeof(long);
	lm->sec_bitmap_len = BITS_TO_LONGS(lm->sec_per_line) * sizeof(long);
	lm->lun_bitmap_len = BITS_TO_LONGS(geo->all_luns) * sizeof(long);
	lm->mid_thrs = lm->sec_per_line / 2;
	lm->high_thrs = lm->sec_per_line / 4;
	lm->meta_distance = (geo->all_luns / 2) * pblk->min_write_pgs;

	/* Calculate necessary pages for smeta. See comment over struct
	 * line_smeta definition
	 */
	i = 1;
add_smeta_page:
	lm->smeta_sec = i * geo->ws_opt;
	lm->smeta_len = lm->smeta_sec * geo->csecs;

	smeta_len = sizeof(struct line_smeta) + lm->lun_bitmap_len;
	if (smeta_len > lm->smeta_len) {
		i++;
		goto add_smeta_page;
	}

	/* Calculate necessary pages for emeta. See comment over struct
	 * line_emeta definition
	 */
	i = 1;
add_emeta_page:
	lm->emeta_sec[0] = i * geo->ws_opt;
	lm->emeta_len[0] = lm->emeta_sec[0] * geo->csecs;

	emeta_len = calc_emeta_len(pblk);
	if (emeta_len > lm->emeta_len[0]) {
		i++;
		goto add_emeta_page;
	}

	lm->emeta_bb = geo->all_luns > i ? geo->all_luns - i : 0;

	lm->min_blk_line = 1;
	if (geo->all_luns > 1)
		lm->min_blk_line += DIV_ROUND_UP(lm->smeta_sec +
					lm->emeta_sec[0], geo->clba);

	if (lm->min_blk_line > lm->blk_per_line) {
		pblk_err(pblk, "config. not supported. Min. LUN in line:%d\n",
							lm->blk_per_line);
		return -EINVAL;
	}

	return 0;
}