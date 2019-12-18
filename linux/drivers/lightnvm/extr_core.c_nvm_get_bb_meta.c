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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ blk; int ch; int lun; } ;
struct ppa_addr {TYPE_1__ g; scalar_t__ ppa; } ;
struct nvm_geo {int num_chk; int pln_mode; int num_ch; int num_lun; } ;
struct nvm_dev {TYPE_2__* ops; struct nvm_geo geo; } ;
struct nvm_chk_meta {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {int (* get_bb_tbl ) (struct nvm_dev*,struct ppa_addr,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ppa_addr dev_to_generic_addr (struct nvm_dev*,struct ppa_addr) ; 
 struct ppa_addr generic_to_dev_addr (struct nvm_dev*,struct ppa_addr) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int nvm_bb_to_chunk (struct nvm_dev*,struct ppa_addr,int /*<<< orphan*/ *,int,struct nvm_chk_meta*) ; 
 int stub1 (struct nvm_dev*,struct ppa_addr,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvm_get_bb_meta(struct nvm_dev *dev, sector_t slba,
			   int nchks, struct nvm_chk_meta *meta)
{
	struct nvm_geo *geo = &dev->geo;
	struct ppa_addr ppa;
	u8 *blks;
	int ch, lun, nr_blks;
	int ret = 0;

	ppa.ppa = slba;
	ppa = dev_to_generic_addr(dev, ppa);

	if (ppa.g.blk != 0)
		return -EINVAL;

	if ((nchks % geo->num_chk) != 0)
		return -EINVAL;

	nr_blks = geo->num_chk * geo->pln_mode;

	blks = kmalloc(nr_blks, GFP_KERNEL);
	if (!blks)
		return -ENOMEM;

	for (ch = ppa.g.ch; ch < geo->num_ch; ch++) {
		for (lun = ppa.g.lun; lun < geo->num_lun; lun++) {
			struct ppa_addr ppa_gen, ppa_dev;

			if (!nchks)
				goto done;

			ppa_gen.ppa = 0;
			ppa_gen.g.ch = ch;
			ppa_gen.g.lun = lun;
			ppa_dev = generic_to_dev_addr(dev, ppa_gen);

			ret = dev->ops->get_bb_tbl(dev, ppa_dev, blks);
			if (ret)
				goto done;

			ret = nvm_bb_to_chunk(dev, ppa_gen, blks, nr_blks,
									meta);
			if (ret)
				goto done;

			meta += geo->num_chk;
			nchks -= geo->num_chk;
		}
	}
done:
	kfree(blks);
	return ret;
}