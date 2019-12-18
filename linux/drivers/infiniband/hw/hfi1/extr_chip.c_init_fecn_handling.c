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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct rsm_rule_data {int field1_off; int field2_off; int index1_off; int index1_width; int mask1; int value1; int mask2; int value2; scalar_t__ index2_width; scalar_t__ index2_off; scalar_t__ pkt_type; scalar_t__ offset; } ;
struct rsm_map_table {int used; int* map; } ;
struct hfi1_devdata {int first_dyn_alloc_ctxt; int num_rcv_contexts; } ;

/* Variables and functions */
 scalar_t__ HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 int NUM_MAP_ENTRIES ; 
 int RCV_RSM_MAP_TABLE_RCV_CONTEXT_A_MASK ; 
 int /*<<< orphan*/  RSM_INS_FECN ; 
 int /*<<< orphan*/  TID_RDMA ; 
 int /*<<< orphan*/  add_rsm_rule (struct hfi1_devdata*,int /*<<< orphan*/ ,struct rsm_rule_data*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 

__attribute__((used)) static void init_fecn_handling(struct hfi1_devdata *dd,
			       struct rsm_map_table *rmt)
{
	struct rsm_rule_data rrd;
	u64 reg;
	int i, idx, regoff, regidx, start;
	u8 offset;
	u32 total_cnt;

	if (HFI1_CAP_IS_KSET(TID_RDMA))
		/* Exclude context 0 */
		start = 1;
	else
		start = dd->first_dyn_alloc_ctxt;

	total_cnt = dd->num_rcv_contexts - start;

	/* there needs to be enough room in the map table */
	if (rmt->used + total_cnt >= NUM_MAP_ENTRIES) {
		dd_dev_err(dd, "FECN handling disabled - too many contexts allocated\n");
		return;
	}

	/*
	 * RSM will extract the destination context as an index into the
	 * map table.  The destination contexts are a sequential block
	 * in the range start...num_rcv_contexts-1 (inclusive).
	 * Map entries are accessed as offset + extracted value.  Adjust
	 * the added offset so this sequence can be placed anywhere in
	 * the table - as long as the entries themselves do not wrap.
	 * There are only enough bits in offset for the table size, so
	 * start with that to allow for a "negative" offset.
	 */
	offset = (u8)(NUM_MAP_ENTRIES + rmt->used - start);

	for (i = start, idx = rmt->used; i < dd->num_rcv_contexts;
	     i++, idx++) {
		/* replace with identity mapping */
		regoff = (idx % 8) * 8;
		regidx = idx / 8;
		reg = rmt->map[regidx];
		reg &= ~(RCV_RSM_MAP_TABLE_RCV_CONTEXT_A_MASK << regoff);
		reg |= (u64)i << regoff;
		rmt->map[regidx] = reg;
	}

	/*
	 * For RSM intercept of Expected FECN packets:
	 * o packet type 0 - expected
	 * o match on F (bit 95), using select/match 1, and
	 * o match on SH (bit 133), using select/match 2.
	 *
	 * Use index 1 to extract the 8-bit receive context from DestQP
	 * (start at bit 64).  Use that as the RSM map table index.
	 */
	rrd.offset = offset;
	rrd.pkt_type = 0;
	rrd.field1_off = 95;
	rrd.field2_off = 133;
	rrd.index1_off = 64;
	rrd.index1_width = 8;
	rrd.index2_off = 0;
	rrd.index2_width = 0;
	rrd.mask1 = 1;
	rrd.value1 = 1;
	rrd.mask2 = 1;
	rrd.value2 = 1;

	/* add rule 1 */
	add_rsm_rule(dd, RSM_INS_FECN, &rrd);

	rmt->used += total_cnt;
}