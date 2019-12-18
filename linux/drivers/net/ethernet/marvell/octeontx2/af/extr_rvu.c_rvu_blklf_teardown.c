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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rvu_block {scalar_t__ addr; int /*<<< orphan*/  type; } ;
struct rvu {int /*<<< orphan*/  dev; TYPE_1__* hw; } ;
struct TYPE_2__ {struct rvu_block* block; } ;

/* Variables and functions */
 scalar_t__ BLKADDR_NIX0 ; 
 scalar_t__ BLKADDR_NPA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int rvu_get_lf (struct rvu*,struct rvu_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 
 int rvu_get_rsrc_mapcount (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_lf_reset (struct rvu*,struct rvu_block*,int) ; 
 int /*<<< orphan*/  rvu_nix_lf_teardown (struct rvu*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  rvu_npa_lf_teardown (struct rvu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rvu_blklf_teardown(struct rvu *rvu, u16 pcifunc, u8 blkaddr)
{
	struct rvu_block *block;
	int slot, lf, num_lfs;
	int err;

	block = &rvu->hw->block[blkaddr];
	num_lfs = rvu_get_rsrc_mapcount(rvu_get_pfvf(rvu, pcifunc),
					block->type);
	if (!num_lfs)
		return;
	for (slot = 0; slot < num_lfs; slot++) {
		lf = rvu_get_lf(rvu, block, pcifunc, slot);
		if (lf < 0)
			continue;

		/* Cleanup LF and reset it */
		if (block->addr == BLKADDR_NIX0)
			rvu_nix_lf_teardown(rvu, pcifunc, block->addr, lf);
		else if (block->addr == BLKADDR_NPA)
			rvu_npa_lf_teardown(rvu, pcifunc, lf);

		err = rvu_lf_reset(rvu, block, lf);
		if (err) {
			dev_err(rvu->dev, "Failed to reset blkaddr %d LF%d\n",
				block->addr, lf);
		}
	}
}