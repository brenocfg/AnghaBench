#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pnd2_pvt {int* dimm_geom; } ;
struct mem_ctl_info {int /*<<< orphan*/  n_layers; int /*<<< orphan*/  dimms; int /*<<< orphan*/  layers; struct pnd2_pvt* pvt_info; } ;
struct dimm_info {int grain; int /*<<< orphan*/  label; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  mtype; int /*<<< orphan*/  dtype; int /*<<< orphan*/  nr_pages; } ;
struct d_cr_drp0 {scalar_t__ addrdec; scalar_t__ dden; scalar_t__ dwid; int rken0; int rken1; } ;
struct TYPE_3__ {scalar_t__ addrdec; scalar_t__ dden; scalar_t__ dwid; unsigned long rowbits; unsigned long colbits; } ;

/* Variables and functions */
 int APL_NUM_CHANNELS ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  DEV_X16 ; 
 int /*<<< orphan*/  DEV_X8 ; 
 struct dimm_info* EDAC_DIMM_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 int /*<<< orphan*/  MEM_DDR3 ; 
 int /*<<< orphan*/  MiB_TO_PAGES (int) ; 
 int chan_mask ; 
 TYPE_1__* dimms ; 
 struct d_cr_drp0* drp0 ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static void apl_get_dimm_config(struct mem_ctl_info *mci)
{
	struct pnd2_pvt	*pvt = mci->pvt_info;
	struct dimm_info *dimm;
	struct d_cr_drp0 *d;
	u64	capacity;
	int	i, g;

	for (i = 0; i < APL_NUM_CHANNELS; i++) {
		if (!(chan_mask & BIT(i)))
			continue;

		dimm = EDAC_DIMM_PTR(mci->layers, mci->dimms, mci->n_layers, i, 0, 0);
		if (!dimm) {
			edac_dbg(0, "No allocated DIMM for channel %d\n", i);
			continue;
		}

		d = &drp0[i];
		for (g = 0; g < ARRAY_SIZE(dimms); g++)
			if (dimms[g].addrdec == d->addrdec &&
			    dimms[g].dden == d->dden &&
			    dimms[g].dwid == d->dwid)
				break;

		if (g == ARRAY_SIZE(dimms)) {
			edac_dbg(0, "Channel %d: unrecognized DIMM\n", i);
			continue;
		}

		pvt->dimm_geom[i] = g;
		capacity = (d->rken0 + d->rken1) * 8 * (1ul << dimms[g].rowbits) *
				   (1ul << dimms[g].colbits);
		edac_dbg(0, "Channel %d: %lld MByte DIMM\n", i, capacity >> (20 - 3));
		dimm->nr_pages = MiB_TO_PAGES(capacity >> (20 - 3));
		dimm->grain = 32;
		dimm->dtype = (d->dwid == 0) ? DEV_X8 : DEV_X16;
		dimm->mtype = MEM_DDR3;
		dimm->edac_mode = EDAC_SECDED;
		snprintf(dimm->label, sizeof(dimm->label), "Slice#%d_Chan#%d", i / 2, i % 2);
	}
}