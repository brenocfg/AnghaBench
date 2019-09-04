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
typedef  void u8 ;
struct pblk_lun {int dummy; } ;
struct pblk {struct pblk_lun* luns; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int num_chk; int pln_mode; int all_luns; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int pblk_bb_get_tbl (struct nvm_tgt_dev*,struct pblk_lun*,void*,int) ; 

__attribute__((used)) static void *pblk_bb_get_meta(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	u8 *meta;
	int i, nr_blks, blk_per_lun;
	int ret;

	blk_per_lun = geo->num_chk * geo->pln_mode;
	nr_blks = blk_per_lun * geo->all_luns;

	meta = kmalloc(nr_blks, GFP_KERNEL);
	if (!meta)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < geo->all_luns; i++) {
		struct pblk_lun *rlun = &pblk->luns[i];
		u8 *meta_pos = meta + i * blk_per_lun;

		ret = pblk_bb_get_tbl(dev, rlun, meta_pos, blk_per_lun);
		if (ret) {
			kfree(meta);
			return ERR_PTR(-EIO);
		}
	}

	return meta;
}