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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct amd64_pvt {int dummy; } ;

/* Variables and functions */
 int BIT_64 (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  amd64_warn (char*,int) ; 
 int /*<<< orphan*/  dct_ganging_enabled (struct amd64_pvt*) ; 
 scalar_t__ dct_high_range_enabled (struct amd64_pvt*) ; 
 scalar_t__ dct_interleave_enabled (struct amd64_pvt*) ; 
 int dct_sel_baseaddr (struct amd64_pvt*) ; 
 int dct_sel_interleave_addr (struct amd64_pvt*) ; 
 int dhar_base (struct amd64_pvt*) ; 
 scalar_t__ dhar_valid (struct amd64_pvt*) ; 
 int dram_dst_node (struct amd64_pvt*,unsigned int) ; 
 int dram_intlv_en (struct amd64_pvt*,unsigned int) ; 
 int dram_intlv_sel (struct amd64_pvt*,unsigned int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,...) ; 
 int f1x_determine_channel (struct amd64_pvt*,int,int,int) ; 
 int f1x_get_norm_dct_addr (struct amd64_pvt*,unsigned int,int,int,int) ; 
 int f1x_lookup_addr_in_dct (int,int,int) ; 
 int f1x_swap_interleaved_region (struct amd64_pvt*,int) ; 
 int /*<<< orphan*/  get_dram_limit (struct amd64_pvt*,unsigned int) ; 
 int hweight8 (int) ; 

__attribute__((used)) static int f1x_match_to_this_node(struct amd64_pvt *pvt, unsigned range,
				  u64 sys_addr, int *chan_sel)
{
	int cs_found = -EINVAL;
	u64 chan_addr;
	u32 dct_sel_base;
	u8 channel;
	bool high_range = false;

	u8 node_id    = dram_dst_node(pvt, range);
	u8 intlv_en   = dram_intlv_en(pvt, range);
	u32 intlv_sel = dram_intlv_sel(pvt, range);

	edac_dbg(1, "(range %d) SystemAddr= 0x%llx Limit=0x%llx\n",
		 range, sys_addr, get_dram_limit(pvt, range));

	if (dhar_valid(pvt) &&
	    dhar_base(pvt) <= sys_addr &&
	    sys_addr < BIT_64(32)) {
		amd64_warn("Huh? Address is in the MMIO hole: 0x%016llx\n",
			    sys_addr);
		return -EINVAL;
	}

	if (intlv_en && (intlv_sel != ((sys_addr >> 12) & intlv_en)))
		return -EINVAL;

	sys_addr = f1x_swap_interleaved_region(pvt, sys_addr);

	dct_sel_base = dct_sel_baseaddr(pvt);

	/*
	 * check whether addresses >= DctSelBaseAddr[47:27] are to be used to
	 * select between DCT0 and DCT1.
	 */
	if (dct_high_range_enabled(pvt) &&
	   !dct_ganging_enabled(pvt) &&
	   ((sys_addr >> 27) >= (dct_sel_base >> 11)))
		high_range = true;

	channel = f1x_determine_channel(pvt, sys_addr, high_range, intlv_en);

	chan_addr = f1x_get_norm_dct_addr(pvt, range, sys_addr,
					  high_range, dct_sel_base);

	/* Remove node interleaving, see F1x120 */
	if (intlv_en)
		chan_addr = ((chan_addr >> (12 + hweight8(intlv_en))) << 12) |
			    (chan_addr & 0xfff);

	/* remove channel interleave */
	if (dct_interleave_enabled(pvt) &&
	   !dct_high_range_enabled(pvt) &&
	   !dct_ganging_enabled(pvt)) {

		if (dct_sel_interleave_addr(pvt) != 1) {
			if (dct_sel_interleave_addr(pvt) == 0x3)
				/* hash 9 */
				chan_addr = ((chan_addr >> 10) << 9) |
					     (chan_addr & 0x1ff);
			else
				/* A[6] or hash 6 */
				chan_addr = ((chan_addr >> 7) << 6) |
					     (chan_addr & 0x3f);
		} else
			/* A[12] */
			chan_addr = ((chan_addr >> 13) << 12) |
				     (chan_addr & 0xfff);
	}

	edac_dbg(1, "   Normalized DCT addr: 0x%llx\n", chan_addr);

	cs_found = f1x_lookup_addr_in_dct(chan_addr, node_id, channel);

	if (cs_found >= 0)
		*chan_sel = channel;

	return cs_found;
}