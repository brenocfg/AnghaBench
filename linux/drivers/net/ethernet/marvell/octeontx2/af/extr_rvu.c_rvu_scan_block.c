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
typedef  int u64 ;
struct rvu_pfvf {int dummy; } ;
struct TYPE_2__ {int max; int /*<<< orphan*/  bmap; } ;
struct rvu_block {int lfcfg_reg; int lfshift; TYPE_1__ lf; int /*<<< orphan*/  addr; } ;
struct rvu {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int) ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_set_msix_offset (struct rvu*,struct rvu_pfvf*,struct rvu_block*,int) ; 
 int /*<<< orphan*/  rvu_update_rsrc_map (struct rvu*,struct rvu_pfvf*,struct rvu_block*,int,int,int) ; 

__attribute__((used)) static void rvu_scan_block(struct rvu *rvu, struct rvu_block *block)
{
	struct rvu_pfvf *pfvf;
	u64 cfg;
	int lf;

	for (lf = 0; lf < block->lf.max; lf++) {
		cfg = rvu_read64(rvu, block->addr,
				 block->lfcfg_reg | (lf << block->lfshift));
		if (!(cfg & BIT_ULL(63)))
			continue;

		/* Set this resource as being used */
		__set_bit(lf, block->lf.bmap);

		/* Get, to whom this LF is attached */
		pfvf = rvu_get_pfvf(rvu, (cfg >> 8) & 0xFFFF);
		rvu_update_rsrc_map(rvu, pfvf, block,
				    (cfg >> 8) & 0xFFFF, lf, true);

		/* Set start MSIX vector for this LF within this PF/VF */
		rvu_set_msix_offset(rvu, pfvf, block, lf);
	}
}