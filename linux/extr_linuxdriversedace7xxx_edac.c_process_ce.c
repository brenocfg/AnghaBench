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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {int dummy; } ;
struct e7xxx_error_info {int dram_celog_add; int /*<<< orphan*/  dram_celog_syndrome; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int e7xxx_find_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int edac_mc_find_csrow_by_page (struct mem_ctl_info*,int) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,char*,char*) ; 

__attribute__((used)) static void process_ce(struct mem_ctl_info *mci, struct e7xxx_error_info *info)
{
	u32 error_1b, page;
	u16 syndrome;
	int row;
	int channel;

	edac_dbg(3, "\n");
	/* read the error address */
	error_1b = info->dram_celog_add;
	/* FIXME - should use PAGE_SHIFT */
	page = error_1b >> 6;	/* convert the address to 4k page */
	/* read the syndrome */
	syndrome = info->dram_celog_syndrome;
	/* FIXME - check for -1 */
	row = edac_mc_find_csrow_by_page(mci, page);
	/* convert syndrome to channel */
	channel = e7xxx_find_channel(syndrome);
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, page, 0, syndrome,
			     row, channel, -1, "e7xxx CE", "");
}