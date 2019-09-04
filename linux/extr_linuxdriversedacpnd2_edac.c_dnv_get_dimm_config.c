#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mem_ctl_info {int /*<<< orphan*/  n_layers; int /*<<< orphan*/  dimms; int /*<<< orphan*/  layers; } ;
struct dimm_info {int grain; int mtype; int /*<<< orphan*/  label; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  dtype; int /*<<< orphan*/  nr_pages; } ;
struct d_cr_drp {int rken0; int rken1; int rken2; int rken3; size_t dimmdwid0; size_t dimmdwid1; } ;
struct TYPE_6__ {int ca11; } ;
struct TYPE_5__ {int row14; int row15; int row16; int row17; } ;
struct TYPE_4__ {scalar_t__ ddr4en; } ;

/* Variables and functions */
 int DNV_MAX_DIMMS ; 
 int DNV_NUM_CHANNELS ; 
 struct dimm_info* EDAC_DIMM_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 int MEM_DDR3 ; 
 int MEM_DDR4 ; 
 int /*<<< orphan*/  MiB_TO_PAGES (int) ; 
 TYPE_3__* dmap1 ; 
 TYPE_2__* dmap4 ; 
 int /*<<< orphan*/ * dnv_dtypes ; 
 struct d_cr_drp* drp ; 
 TYPE_1__ dsch ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static void dnv_get_dimm_config(struct mem_ctl_info *mci)
{
	int	i, j, ranks_of_dimm[DNV_MAX_DIMMS], banks, rowbits, colbits, memtype;
	struct dimm_info *dimm;
	struct d_cr_drp *d;
	u64	capacity;

	if (dsch.ddr4en) {
		memtype = MEM_DDR4;
		banks = 16;
		colbits = 10;
	} else {
		memtype = MEM_DDR3;
		banks = 8;
	}

	for (i = 0; i < DNV_NUM_CHANNELS; i++) {
		if (dmap4[i].row14 == 31)
			rowbits = 14;
		else if (dmap4[i].row15 == 31)
			rowbits = 15;
		else if (dmap4[i].row16 == 31)
			rowbits = 16;
		else if (dmap4[i].row17 == 31)
			rowbits = 17;
		else
			rowbits = 18;

		if (memtype == MEM_DDR3) {
			if (dmap1[i].ca11 != 0x3f)
				colbits = 12;
			else
				colbits = 10;
		}

		d = &drp[i];
		/* DIMM0 is present if rank0 and/or rank1 is enabled */
		ranks_of_dimm[0] = d->rken0 + d->rken1;
		/* DIMM1 is present if rank2 and/or rank3 is enabled */
		ranks_of_dimm[1] = d->rken2 + d->rken3;

		for (j = 0; j < DNV_MAX_DIMMS; j++) {
			if (!ranks_of_dimm[j])
				continue;

			dimm = EDAC_DIMM_PTR(mci->layers, mci->dimms, mci->n_layers, i, j, 0);
			if (!dimm) {
				edac_dbg(0, "No allocated DIMM for channel %d DIMM %d\n", i, j);
				continue;
			}

			capacity = ranks_of_dimm[j] * banks * (1ul << rowbits) * (1ul << colbits);
			edac_dbg(0, "Channel %d DIMM %d: %lld MByte DIMM\n", i, j, capacity >> (20 - 3));
			dimm->nr_pages = MiB_TO_PAGES(capacity >> (20 - 3));
			dimm->grain = 32;
			dimm->dtype = dnv_dtypes[j ? d->dimmdwid0 : d->dimmdwid1];
			dimm->mtype = memtype;
			dimm->edac_mode = EDAC_SECDED;
			snprintf(dimm->label, sizeof(dimm->label), "Chan#%d_DIMM#%d", i, j);
		}
	}
}