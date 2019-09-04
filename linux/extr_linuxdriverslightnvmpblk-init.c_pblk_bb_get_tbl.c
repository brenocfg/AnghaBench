#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  ch; } ;
struct ppa_addr {TYPE_2__ g; scalar_t__ ppa; } ;
struct TYPE_6__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  ch; } ;
struct TYPE_4__ {TYPE_3__ g; } ;
struct pblk_lun {TYPE_1__ bppa; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EIO ; 
 int nvm_bb_tbl_fold (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int nvm_get_tgt_bb_tbl (struct nvm_tgt_dev*,struct ppa_addr,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pblk_bb_get_tbl(struct nvm_tgt_dev *dev, struct pblk_lun *rlun,
			   u8 *blks, int nr_blks)
{
	struct ppa_addr ppa;
	int ret;

	ppa.ppa = 0;
	ppa.g.ch = rlun->bppa.g.ch;
	ppa.g.lun = rlun->bppa.g.lun;

	ret = nvm_get_tgt_bb_tbl(dev, ppa, blks);
	if (ret)
		return ret;

	nr_blks = nvm_bb_tbl_fold(dev->parent, blks, nr_blks);
	if (nr_blks < 0)
		return -EIO;

	return 0;
}