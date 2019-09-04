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
struct pblk_line_meta {int smeta_len; int smeta_sec; int* emeta_len; int* emeta_sec; int emeta_bb; int sec_bitmap_len; int blk_bitmap_len; int lun_bitmap_len; int blk_per_line; int sec_per_line; } ;
struct pblk {struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int clba; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int snprintf (char*,int,char*,int,int,...) ; 

__attribute__((used)) static ssize_t pblk_sysfs_lines_info(struct pblk *pblk, char *page)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	ssize_t sz = 0;

	sz = snprintf(page, PAGE_SIZE - sz,
				"smeta - len:%d, secs:%d\n",
					lm->smeta_len, lm->smeta_sec);
	sz += snprintf(page + sz, PAGE_SIZE - sz,
				"emeta - len:%d, sec:%d, bb_start:%d\n",
					lm->emeta_len[0], lm->emeta_sec[0],
					lm->emeta_bb);
	sz += snprintf(page + sz, PAGE_SIZE - sz,
				"bitmap lengths: sec:%d, blk:%d, lun:%d\n",
					lm->sec_bitmap_len,
					lm->blk_bitmap_len,
					lm->lun_bitmap_len);
	sz += snprintf(page + sz, PAGE_SIZE - sz,
				"blk_line:%d, sec_line:%d, sec_blk:%d\n",
					lm->blk_per_line,
					lm->sec_per_line,
					geo->clba);

	return sz;
}