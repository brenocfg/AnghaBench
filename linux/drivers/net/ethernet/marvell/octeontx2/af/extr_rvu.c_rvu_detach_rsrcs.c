#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct rvu_hwinfo {struct rvu_block* block; } ;
struct TYPE_2__ {int /*<<< orphan*/  bmap; } ;
struct rvu_block {int /*<<< orphan*/  type; TYPE_1__ lf; } ;
struct rvu {int /*<<< orphan*/  rsrc_lock; struct rvu_hwinfo* hw; } ;
struct rsrc_detach {int /*<<< orphan*/  cptlfs; int /*<<< orphan*/  timlfs; int /*<<< orphan*/  ssow; int /*<<< orphan*/  sso; int /*<<< orphan*/  nixlf; int /*<<< orphan*/  npalf; scalar_t__ partial; } ;

/* Variables and functions */
 int BLKADDR_CPT0 ; 
 int BLKADDR_NIX0 ; 
 int BLKADDR_NPA ; 
 int BLKADDR_SSO ; 
 int BLKADDR_SSOW ; 
 int BLKADDR_TIM ; 
 int BLK_COUNT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvu_detach_block (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvu_detach_rsrcs(struct rvu *rvu, struct rsrc_detach *detach,
			    u16 pcifunc)
{
	struct rvu_hwinfo *hw = rvu->hw;
	bool detach_all = true;
	struct rvu_block *block;
	int blkid;

	mutex_lock(&rvu->rsrc_lock);

	/* Check for partial resource detach */
	if (detach && detach->partial)
		detach_all = false;

	/* Check for RVU block's LFs attached to this func,
	 * if so, detach them.
	 */
	for (blkid = 0; blkid < BLK_COUNT; blkid++) {
		block = &hw->block[blkid];
		if (!block->lf.bmap)
			continue;
		if (!detach_all && detach) {
			if (blkid == BLKADDR_NPA && !detach->npalf)
				continue;
			else if ((blkid == BLKADDR_NIX0) && !detach->nixlf)
				continue;
			else if ((blkid == BLKADDR_SSO) && !detach->sso)
				continue;
			else if ((blkid == BLKADDR_SSOW) && !detach->ssow)
				continue;
			else if ((blkid == BLKADDR_TIM) && !detach->timlfs)
				continue;
			else if ((blkid == BLKADDR_CPT0) && !detach->cptlfs)
				continue;
		}
		rvu_detach_block(rvu, pcifunc, block->type);
	}

	mutex_unlock(&rvu->rsrc_lock);
	return 0;
}