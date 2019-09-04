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
typedef  scalar_t__ u32 ;
struct ti_edac {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  n_layers; int /*<<< orphan*/  dimms; int /*<<< orphan*/  layers; struct ti_edac* pvt_info; } ;
struct dimm_info {int grain; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  mtype; scalar_t__ nr_pages; void* dtype; } ;

/* Variables and functions */
 void* DEV_X16 ; 
 void* DEV_X32 ; 
 void* DEV_X64 ; 
 scalar_t__ ECC_ENABLED ; 
 struct dimm_info* EDAC_DIMM_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDAC_NONE ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 int /*<<< orphan*/  EMIF_ECC_CTRL ; 
 int /*<<< orphan*/  EMIF_SDRAM_CONFIG ; 
 scalar_t__ EMIF_TYPE_DRA7 ; 
 int /*<<< orphan*/  MEM_DDR2 ; 
 int /*<<< orphan*/  MEM_DDR3 ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ SDRAM_IBANK_MASK ; 
 scalar_t__ SDRAM_IBANK_SHIFT ; 
 scalar_t__ SDRAM_K2_EBANK_MASK ; 
 scalar_t__ SDRAM_K2_EBANK_SHIFT ; 
 scalar_t__ SDRAM_K2_IBANK_MASK ; 
 scalar_t__ SDRAM_K2_IBANK_SHIFT ; 
 scalar_t__ SDRAM_K2_NARROW_MODE_MASK ; 
 scalar_t__ SDRAM_K2_NARROW_MODE_SHIFT ; 
 scalar_t__ SDRAM_K2_PAGESIZE_MASK ; 
 scalar_t__ SDRAM_K2_PAGESIZE_SHIFT ; 
 scalar_t__ SDRAM_NARROW_MODE_MASK ; 
 scalar_t__ SDRAM_PAGESIZE_MASK ; 
 scalar_t__ SDRAM_PAGESIZE_SHIFT ; 
 scalar_t__ SDRAM_ROWSIZE_MASK ; 
 scalar_t__ SDRAM_ROWSIZE_SHIFT ; 
 scalar_t__ SDRAM_TYPE_DDR2 ; 
 scalar_t__ SDRAM_TYPE_MASK ; 
 scalar_t__ ti_edac_readl (struct ti_edac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_edac_setup_dimm(struct mem_ctl_info *mci, u32 type)
{
	struct dimm_info *dimm;
	struct ti_edac *edac = mci->pvt_info;
	int bits;
	u32 val;
	u32 memsize;

	dimm = EDAC_DIMM_PTR(mci->layers, mci->dimms, mci->n_layers, 0, 0, 0);

	val = ti_edac_readl(edac, EMIF_SDRAM_CONFIG);

	if (type == EMIF_TYPE_DRA7) {
		bits = ((val & SDRAM_PAGESIZE_MASK) >> SDRAM_PAGESIZE_SHIFT) + 8;
		bits += ((val & SDRAM_ROWSIZE_MASK) >> SDRAM_ROWSIZE_SHIFT) + 9;
		bits += (val & SDRAM_IBANK_MASK) >> SDRAM_IBANK_SHIFT;

		if (val & SDRAM_NARROW_MODE_MASK) {
			bits++;
			dimm->dtype = DEV_X16;
		} else {
			bits += 2;
			dimm->dtype = DEV_X32;
		}
	} else {
		bits = 16;
		bits += ((val & SDRAM_K2_PAGESIZE_MASK) >>
			SDRAM_K2_PAGESIZE_SHIFT) + 8;
		bits += (val & SDRAM_K2_IBANK_MASK) >> SDRAM_K2_IBANK_SHIFT;
		bits += (val & SDRAM_K2_EBANK_MASK) >> SDRAM_K2_EBANK_SHIFT;

		val = (val & SDRAM_K2_NARROW_MODE_MASK) >>
			SDRAM_K2_NARROW_MODE_SHIFT;
		switch (val) {
		case 0:
			bits += 3;
			dimm->dtype = DEV_X64;
			break;
		case 1:
			bits += 2;
			dimm->dtype = DEV_X32;
			break;
		case 2:
			bits++;
			dimm->dtype = DEV_X16;
			break;
		}
	}

	memsize = 1 << bits;

	dimm->nr_pages = memsize >> PAGE_SHIFT;
	dimm->grain = 4;
	if ((val & SDRAM_TYPE_MASK) == SDRAM_TYPE_DDR2)
		dimm->mtype = MEM_DDR2;
	else
		dimm->mtype = MEM_DDR3;

	val = ti_edac_readl(edac, EMIF_ECC_CTRL);
	if (val & ECC_ENABLED)
		dimm->edac_mode = EDAC_SECDED;
	else
		dimm->edac_mode = EDAC_NONE;
}