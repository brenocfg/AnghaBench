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
struct pblk_lun {int /*<<< orphan*/  wr_sem; int /*<<< orphan*/  bppa; } ;
struct pblk {struct pblk_lun* luns; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ num_lun; int all_luns; int num_ch; } ;
struct nvm_tgt_dev {int /*<<< orphan*/ * luns; struct nvm_geo geo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pblk_lun* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pblk_luns_init(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_lun *rlun;
	int i;

	/* TODO: Implement unbalanced LUN support */
	if (geo->num_lun < 0) {
		pblk_err(pblk, "unbalanced LUN config.\n");
		return -EINVAL;
	}

	pblk->luns = kcalloc(geo->all_luns, sizeof(struct pblk_lun),
								GFP_KERNEL);
	if (!pblk->luns)
		return -ENOMEM;

	for (i = 0; i < geo->all_luns; i++) {
		/* Stripe across channels */
		int ch = i % geo->num_ch;
		int lun_raw = i / geo->num_ch;
		int lunid = lun_raw + ch * geo->num_lun;

		rlun = &pblk->luns[i];
		rlun->bppa = dev->luns[lunid];

		sema_init(&rlun->wr_sem, 1);
	}

	return 0;
}