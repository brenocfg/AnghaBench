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
typedef  int u8 ;
struct nvm_geo {int num_chk; int pln_mode; } ;
struct nvm_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int EINVAL ; 
 int NVM_BLK_T_BAD ; 
 int NVM_BLK_T_GRWN_BAD ; 

int nvm_bb_tbl_fold(struct nvm_dev *dev, u8 *blks, int nr_blks)
{
	struct nvm_geo *geo = &dev->geo;
	int blk, offset, pl, blktype;

	if (nr_blks != geo->num_chk * geo->pln_mode)
		return -EINVAL;

	for (blk = 0; blk < geo->num_chk; blk++) {
		offset = blk * geo->pln_mode;
		blktype = blks[offset];

		/* Bad blocks on any planes take precedence over other types */
		for (pl = 0; pl < geo->pln_mode; pl++) {
			if (blks[offset + pl] &
					(NVM_BLK_T_BAD|NVM_BLK_T_GRWN_BAD)) {
				blktype = blks[offset + pl];
				break;
			}
		}

		blks[blk] = blktype;
	}

	return geo->num_chk;
}