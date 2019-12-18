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
typedef  unsigned long long u64 ;
struct rvu_pfvf {int dummy; } ;
struct rvu_hwinfo {struct rvu_block* block; } ;
struct TYPE_2__ {int /*<<< orphan*/  bmap; } ;
struct rvu_block {int lfcfg_reg; int lfshift; TYPE_1__ lf; } ;
struct rvu {struct rvu_hwinfo* hw; } ;

/* Variables and functions */
 int rvu_alloc_rsrc (TYPE_1__*) ; 
 int rvu_get_blkaddr (struct rvu*,int,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int) ; 
 int /*<<< orphan*/  rvu_set_msix_offset (struct rvu*,struct rvu_pfvf*,struct rvu_block*,int) ; 
 int /*<<< orphan*/  rvu_update_rsrc_map (struct rvu*,struct rvu_pfvf*,struct rvu_block*,int,int,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int,unsigned long long) ; 

__attribute__((used)) static void rvu_attach_block(struct rvu *rvu, int pcifunc,
			     int blktype, int num_lfs)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcifunc);
	struct rvu_hwinfo *hw = rvu->hw;
	struct rvu_block *block;
	int slot, lf;
	int blkaddr;
	u64 cfg;

	if (!num_lfs)
		return;

	blkaddr = rvu_get_blkaddr(rvu, blktype, 0);
	if (blkaddr < 0)
		return;

	block = &hw->block[blkaddr];
	if (!block->lf.bmap)
		return;

	for (slot = 0; slot < num_lfs; slot++) {
		/* Allocate the resource */
		lf = rvu_alloc_rsrc(&block->lf);
		if (lf < 0)
			return;

		cfg = (1ULL << 63) | (pcifunc << 8) | slot;
		rvu_write64(rvu, blkaddr, block->lfcfg_reg |
			    (lf << block->lfshift), cfg);
		rvu_update_rsrc_map(rvu, pfvf, block,
				    pcifunc, lf, true);

		/* Set start MSIX vector for this LF within this PF/VF */
		rvu_set_msix_offset(rvu, pfvf, block, lf);
	}
}