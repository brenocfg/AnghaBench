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
struct pblk_lun {int /*<<< orphan*/  wr_sem; } ;
struct pblk {struct pblk_lun* luns; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int all_luns; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int find_next_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void pblk_up_rq(struct pblk *pblk, unsigned long *lun_bitmap)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_lun *rlun;
	int num_lun = geo->all_luns;
	int bit = -1;

	while ((bit = find_next_bit(lun_bitmap, num_lun, bit + 1)) < num_lun) {
		rlun = &pblk->luns[bit];
		up(&rlun->wr_sem);
	}
}