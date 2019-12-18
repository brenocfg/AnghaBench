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
typedef  int u8 ;
struct TYPE_3__ {int blk; } ;
struct ppa_addr {TYPE_1__ g; } ;
struct nvm_geo {int num_chk; int pln_mode; int /*<<< orphan*/  clba; } ;
struct nvm_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int /*<<< orphan*/  state; int /*<<< orphan*/  cnlb; int /*<<< orphan*/  slba; scalar_t__ wi; int /*<<< orphan*/  type; scalar_t__ wp; } ;
struct TYPE_4__ {int /*<<< orphan*/  ppa; } ;

/* Variables and functions */
 int NVM_BLK_T_BAD ; 
 int NVM_BLK_T_FREE ; 
 int NVM_BLK_T_GRWN_BAD ; 
 int /*<<< orphan*/  NVM_CHK_ST_OFFLINE ; 
 int /*<<< orphan*/  NVM_CHK_TP_W_SEQ ; 
 TYPE_2__ generic_to_dev_addr (struct nvm_dev*,struct ppa_addr) ; 
 int nvm_bb_chunk_scan (struct nvm_dev*,struct ppa_addr,struct nvm_chk_meta*) ; 

__attribute__((used)) static int nvm_bb_to_chunk(struct nvm_dev *dev, struct ppa_addr ppa,
			   u8 *blks, int nr_blks, struct nvm_chk_meta *meta)
{
	struct nvm_geo *geo = &dev->geo;
	int ret, blk, pl, offset, blktype;

	for (blk = 0; blk < geo->num_chk; blk++) {
		offset = blk * geo->pln_mode;
		blktype = blks[offset];

		for (pl = 0; pl < geo->pln_mode; pl++) {
			if (blks[offset + pl] &
					(NVM_BLK_T_BAD|NVM_BLK_T_GRWN_BAD)) {
				blktype = blks[offset + pl];
				break;
			}
		}

		ppa.g.blk = blk;

		meta->wp = 0;
		meta->type = NVM_CHK_TP_W_SEQ;
		meta->wi = 0;
		meta->slba = generic_to_dev_addr(dev, ppa).ppa;
		meta->cnlb = dev->geo.clba;

		if (blktype == NVM_BLK_T_FREE) {
			ret = nvm_bb_chunk_scan(dev, ppa, meta);
			if (ret)
				return ret;
		} else {
			meta->state = NVM_CHK_ST_OFFLINE;
		}

		meta++;
	}

	return 0;
}