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
typedef  int u64 ;
typedef  size_t u16 ;
struct rvu_pfvf {int /*<<< orphan*/  msix; scalar_t__* msix_lfmap; } ;
struct rvu_block {int msixcfg_reg; int lfshift; int /*<<< orphan*/  addr; } ;
struct rvu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rvu_free_rsrc_contig (int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t rvu_get_msix_offset (struct rvu*,struct rvu_pfvf*,int /*<<< orphan*/ ,int) ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rvu_clear_msix_offset(struct rvu *rvu, struct rvu_pfvf *pfvf,
				  struct rvu_block *block, int lf)
{
	u16 nvecs, vec, offset;
	u64 cfg;

	cfg = rvu_read64(rvu, block->addr, block->msixcfg_reg |
			 (lf << block->lfshift));
	nvecs = (cfg >> 12) & 0xFF;

	/* Clear MSIX offset in LF */
	rvu_write64(rvu, block->addr, block->msixcfg_reg |
		    (lf << block->lfshift), cfg & ~0x7FFULL);

	offset = rvu_get_msix_offset(rvu, pfvf, block->addr, lf);

	/* Update the mapping */
	for (vec = 0; vec < nvecs; vec++)
		pfvf->msix_lfmap[offset + vec] = 0;

	/* Free the same in MSIX bitmap */
	rvu_free_rsrc_contig(&pfvf->msix, nvecs, offset);
}