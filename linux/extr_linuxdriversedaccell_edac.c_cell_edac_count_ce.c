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
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,scalar_t__,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int,char*,char*) ; 

__attribute__((used)) static void cell_edac_count_ce(struct mem_ctl_info *mci, int chan, u64 ar)
{
	struct cell_edac_priv		*priv = mci->pvt_info;
	struct csrow_info		*csrow = mci->csrows[0];
	unsigned long			address, pfn, offset, syndrome;

	dev_dbg(mci->pdev, "ECC CE err on node %d, channel %d, ar = 0x%016llx\n",
		priv->node, chan, ar);

	/* Address decoding is likely a bit bogus, to dbl check */
	address = (ar & 0xffffffffe0000000ul) >> 29;
	if (priv->chanmask == 0x3)
		address = (address << 1) | chan;
	pfn = address >> PAGE_SHIFT;
	offset = address & ~PAGE_MASK;
	syndrome = (ar & 0x000000001fe00000ul) >> 21;

	/* TODO: Decoding of the error address */
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
			     csrow->first_page + pfn, offset, syndrome,
			     0, chan, -1, "", "");
}