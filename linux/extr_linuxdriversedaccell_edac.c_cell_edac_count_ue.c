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
struct mem_ctl_info {int /*<<< orphan*/  pdev; struct csrow_info** csrows; struct cell_edac_priv* pvt_info; } ;
struct csrow_info {scalar_t__ first_page; } ;
struct cell_edac_priv {int chanmask; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,char*) ; 

__attribute__((used)) static void cell_edac_count_ue(struct mem_ctl_info *mci, int chan, u64 ar)
{
	struct cell_edac_priv		*priv = mci->pvt_info;
	struct csrow_info		*csrow = mci->csrows[0];
	unsigned long			address, pfn, offset;

	dev_dbg(mci->pdev, "ECC UE err on node %d, channel %d, ar = 0x%016llx\n",
		priv->node, chan, ar);

	/* Address decoding is likely a bit bogus, to dbl check */
	address = (ar & 0xffffffffe0000000ul) >> 29;
	if (priv->chanmask == 0x3)
		address = (address << 1) | chan;
	pfn = address >> PAGE_SHIFT;
	offset = address & ~PAGE_MASK;

	/* TODO: Decoding of the error address */
	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
			     csrow->first_page + pfn, offset, 0,
			     0, chan, -1, "", "");
}