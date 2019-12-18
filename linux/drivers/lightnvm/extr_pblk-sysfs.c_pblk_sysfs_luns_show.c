#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ch; int lun; } ;
struct TYPE_4__ {TYPE_1__ a; } ;
struct pblk_lun {TYPE_2__ bppa; int /*<<< orphan*/  wr_sem; } ;
struct pblk {struct pblk_lun* luns; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int all_luns; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  down_trylock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t pblk_sysfs_luns_show(struct pblk *pblk, char *page)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_lun *rlun;
	ssize_t sz = 0;
	int i;

	for (i = 0; i < geo->all_luns; i++) {
		int active = 1;

		rlun = &pblk->luns[i];
		if (!down_trylock(&rlun->wr_sem)) {
			active = 0;
			up(&rlun->wr_sem);
		}
		sz += snprintf(page + sz, PAGE_SIZE - sz,
				"pblk: pos:%d, ch:%d, lun:%d - %d\n",
					i,
					rlun->bppa.a.ch,
					rlun->bppa.a.lun,
					active);
	}

	return sz;
}