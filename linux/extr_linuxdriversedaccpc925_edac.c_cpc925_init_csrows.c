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
typedef  int u32 ;
struct mem_ctl_info {int nr_csrows; struct csrow_info** csrows; struct cpc925_mc_pdata* pvt_info; } ;
struct dimm_info {unsigned long nr_pages; int grain; int dtype; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  mtype; } ;
struct csrow_info {unsigned long first_page; unsigned long last_page; int nr_channels; TYPE_1__** channels; } ;
struct cpc925_mc_pdata {scalar_t__ vbase; } ;
typedef  enum dev_type { ____Placeholder_dev_type } dev_type ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int DEV_UNKNOWN ; 
 int DEV_X16 ; 
 int DEV_X8 ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 int MBBAR_BBA_MASK ; 
 int MBBAR_BBA_SHIFT ; 
 int MBMR_BBA_MASK ; 
 int MBMR_BBA_SHIFT ; 
 int MBMR_MODE_MASK ; 
 int MBMR_MODE_SHIFT ; 
 int /*<<< orphan*/  MEM_RDDR ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ REG_MBBAR_OFFSET ; 
 scalar_t__ REG_MBMR_OFFSET ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  get_total_mem (struct cpc925_mc_pdata*) ; 

__attribute__((used)) static void cpc925_init_csrows(struct mem_ctl_info *mci)
{
	struct cpc925_mc_pdata *pdata = mci->pvt_info;
	struct csrow_info *csrow;
	struct dimm_info *dimm;
	enum dev_type dtype;
	int index, j;
	u32 mbmr, mbbar, bba, grain;
	unsigned long row_size, nr_pages, last_nr_pages = 0;

	get_total_mem(pdata);

	for (index = 0; index < mci->nr_csrows; index++) {
		mbmr = __raw_readl(pdata->vbase + REG_MBMR_OFFSET +
				   0x20 * index);
		mbbar = __raw_readl(pdata->vbase + REG_MBBAR_OFFSET +
				   0x20 + index);
		bba = (((mbmr & MBMR_BBA_MASK) >> MBMR_BBA_SHIFT) << 8) |
		       ((mbbar & MBBAR_BBA_MASK) >> MBBAR_BBA_SHIFT);

		if (bba == 0)
			continue; /* not populated */

		csrow = mci->csrows[index];

		row_size = bba * (1UL << 28);	/* 256M */
		csrow->first_page = last_nr_pages;
		nr_pages = row_size >> PAGE_SHIFT;
		csrow->last_page = csrow->first_page + nr_pages - 1;
		last_nr_pages = csrow->last_page + 1;

		switch (csrow->nr_channels) {
		case 1: /* Single channel */
			grain = 32; /* four-beat burst of 32 bytes */
			break;
		case 2: /* Dual channel */
		default:
			grain = 64; /* four-beat burst of 64 bytes */
			break;
		}
		switch ((mbmr & MBMR_MODE_MASK) >> MBMR_MODE_SHIFT) {
		case 6: /* 0110, no way to differentiate X8 VS X16 */
		case 5:	/* 0101 */
		case 8: /* 1000 */
			dtype = DEV_X16;
			break;
		case 7: /* 0111 */
		case 9: /* 1001 */
			dtype = DEV_X8;
			break;
		default:
			dtype = DEV_UNKNOWN;
		break;
		}
		for (j = 0; j < csrow->nr_channels; j++) {
			dimm = csrow->channels[j]->dimm;
			dimm->nr_pages = nr_pages / csrow->nr_channels;
			dimm->mtype = MEM_RDDR;
			dimm->edac_mode = EDAC_SECDED;
			dimm->grain = grain;
			dimm->dtype = dtype;
		}
	}
}