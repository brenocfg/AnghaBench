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
struct mem_ctl_info {int nr_csrows; int /*<<< orphan*/  mc_idx; struct csrow_info** csrows; } ;
struct dimm_info {scalar_t__ nr_pages; } ;
struct csrow_info {int nr_channels; unsigned long first_page; unsigned long last_page; unsigned long page_mask; TYPE_1__** channels; } ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ,unsigned long,...) ; 
 int /*<<< orphan*/  edac_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,unsigned long) ; 

int edac_mc_find_csrow_by_page(struct mem_ctl_info *mci, unsigned long page)
{
	struct csrow_info **csrows = mci->csrows;
	int row, i, j, n;

	edac_dbg(1, "MC%d: 0x%lx\n", mci->mc_idx, page);
	row = -1;

	for (i = 0; i < mci->nr_csrows; i++) {
		struct csrow_info *csrow = csrows[i];
		n = 0;
		for (j = 0; j < csrow->nr_channels; j++) {
			struct dimm_info *dimm = csrow->channels[j]->dimm;
			n += dimm->nr_pages;
		}
		if (n == 0)
			continue;

		edac_dbg(3, "MC%d: first(0x%lx) page(0x%lx) last(0x%lx) mask(0x%lx)\n",
			 mci->mc_idx,
			 csrow->first_page, page, csrow->last_page,
			 csrow->page_mask);

		if ((page >= csrow->first_page) &&
		    (page <= csrow->last_page) &&
		    ((page & csrow->page_mask) ==
		     (csrow->first_page & csrow->page_mask))) {
			row = i;
			break;
		}
	}

	if (row == -1)
		edac_mc_printk(mci, KERN_ERR,
			"could not look up page error address %lx\n",
			(unsigned long)page);

	return row;
}