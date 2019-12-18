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
struct rvu_pfvf {int dummy; } ;
struct rvu_hwinfo {struct rvu_block* block; } ;
struct rvu_block {int lfcfg_reg; int lfshift; int /*<<< orphan*/  lf; int /*<<< orphan*/  type; } ;
struct rvu {struct rvu_hwinfo* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  rvu_clear_msix_offset (struct rvu*,struct rvu_pfvf*,struct rvu_block*,int) ; 
 int /*<<< orphan*/  rvu_free_rsrc (int /*<<< orphan*/ *,int) ; 
 int rvu_get_blkaddr (struct rvu*,int,int) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int) ; 
 int rvu_get_rsrc_mapcount (struct rvu_pfvf*,int /*<<< orphan*/ ) ; 
 int rvu_lookup_rsrc (struct rvu*,struct rvu_block*,int,int) ; 
 int /*<<< orphan*/  rvu_update_rsrc_map (struct rvu*,struct rvu_pfvf*,struct rvu_block*,int,int,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int,int) ; 

__attribute__((used)) static void rvu_detach_block(struct rvu *rvu, int pcifunc, int blktype)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcifunc);
	struct rvu_hwinfo *hw = rvu->hw;
	struct rvu_block *block;
	int slot, lf, num_lfs;
	int blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, blktype, pcifunc);
	if (blkaddr < 0)
		return;

	block = &hw->block[blkaddr];

	num_lfs = rvu_get_rsrc_mapcount(pfvf, block->type);
	if (!num_lfs)
		return;

	for (slot = 0; slot < num_lfs; slot++) {
		lf = rvu_lookup_rsrc(rvu, block, pcifunc, slot);
		if (lf < 0) /* This should never happen */
			continue;

		/* Disable the LF */
		rvu_write64(rvu, blkaddr, block->lfcfg_reg |
			    (lf << block->lfshift), 0x00ULL);

		/* Update SW maintained mapping info as well */
		rvu_update_rsrc_map(rvu, pfvf, block,
				    pcifunc, lf, false);

		/* Free the resource */
		rvu_free_rsrc(&block->lf, lf);

		/* Clear MSIX vector offset for this LF */
		rvu_clear_msix_offset(rvu, pfvf, block, lf);
	}
}