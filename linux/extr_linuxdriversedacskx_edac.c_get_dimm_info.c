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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct skx_imc {int src_id; int lmc; TYPE_2__* chan; int /*<<< orphan*/  mc; } ;
struct dimm_info {int nr_pages; int grain; int /*<<< orphan*/  label; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  mtype; int /*<<< orphan*/  dtype; } ;
struct TYPE_4__ {TYPE_1__* dimms; } ;
struct TYPE_3__ {int rowbits; int colbits; void* fine_grain_bank; void* bank_xor_enable; void* close_pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_SECDED ; 
 void* GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MEM_DDR4 ; 
 int MiB_TO_PAGES (unsigned long long) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned long long,int,int,int,int,int) ; 
 int /*<<< orphan*/  get_width (int /*<<< orphan*/ ) ; 
 int numcol (int /*<<< orphan*/ ) ; 
 int numrank (int /*<<< orphan*/ ) ; 
 int numrow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int) ; 

__attribute__((used)) static int get_dimm_info(u32 mtr, u32 amap, struct dimm_info *dimm,
			 struct skx_imc *imc, int chan, int dimmno)
{
	int  banks = 16, ranks, rows, cols, npages;
	u64 size;

	ranks = numrank(mtr);
	rows = numrow(mtr);
	cols = numcol(mtr);

	/*
	 * Compute size in 8-byte (2^3) words, then shift to MiB (2^20)
	 */
	size = ((1ull << (rows + cols + ranks)) * banks) >> (20 - 3);
	npages = MiB_TO_PAGES(size);

	edac_dbg(0, "mc#%d: channel %d, dimm %d, %lld Mb (%d pages) bank: %d, rank: %d, row: %#x, col: %#x\n",
		 imc->mc, chan, dimmno, size, npages,
		 banks, 1 << ranks, rows, cols);

	imc->chan[chan].dimms[dimmno].close_pg = GET_BITFIELD(mtr, 0, 0);
	imc->chan[chan].dimms[dimmno].bank_xor_enable = GET_BITFIELD(mtr, 9, 9);
	imc->chan[chan].dimms[dimmno].fine_grain_bank = GET_BITFIELD(amap, 0, 0);
	imc->chan[chan].dimms[dimmno].rowbits = rows;
	imc->chan[chan].dimms[dimmno].colbits = cols;

	dimm->nr_pages = npages;
	dimm->grain = 32;
	dimm->dtype = get_width(mtr);
	dimm->mtype = MEM_DDR4;
	dimm->edac_mode = EDAC_SECDED; /* likely better than this */
	snprintf(dimm->label, sizeof(dimm->label), "CPU_SrcID#%u_MC#%u_Chan#%u_DIMM#%u",
		 imc->src_id, imc->lmc, chan, dimmno);

	return 1;
}