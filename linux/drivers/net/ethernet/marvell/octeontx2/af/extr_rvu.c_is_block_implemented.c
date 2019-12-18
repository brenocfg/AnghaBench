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
struct rvu_hwinfo {struct rvu_block* block; } ;
struct rvu_block {int implemented; } ;

/* Variables and functions */
 int BLKADDR_RVUM ; 
 int BLK_COUNT ; 

bool is_block_implemented(struct rvu_hwinfo *hw, int blkaddr)
{
	struct rvu_block *block;

	if (blkaddr < BLKADDR_RVUM || blkaddr >= BLK_COUNT)
		return false;

	block = &hw->block[blkaddr];
	return block->implemented;
}