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
typedef  unsigned int u64 ;
struct rsm_rule_data {unsigned int offset; int pkt_type; unsigned int index1_width; unsigned int index2_width; int /*<<< orphan*/  value2; int /*<<< orphan*/  mask2; int /*<<< orphan*/  value1; int /*<<< orphan*/  mask1; int /*<<< orphan*/  index2_off; int /*<<< orphan*/  index1_off; int /*<<< orphan*/  field2_off; int /*<<< orphan*/  field1_off; } ;
struct rsm_map_table {scalar_t__ used; unsigned int* map; } ;
struct hfi1_devdata {unsigned int qos_shift; unsigned int n_krcv_queues; } ;

/* Variables and functions */
 unsigned int FIRST_KERNEL_KCTXT ; 
 unsigned int HFI1_CTRL_CTXT ; 
 int /*<<< orphan*/  LRH_BTH_MASK ; 
 int /*<<< orphan*/  LRH_BTH_MATCH_OFFSET ; 
 int /*<<< orphan*/  LRH_BTH_VALUE ; 
 int /*<<< orphan*/  LRH_SC_MASK ; 
 int /*<<< orphan*/  LRH_SC_MATCH_OFFSET ; 
 int /*<<< orphan*/  LRH_SC_SELECT_OFFSET ; 
 int /*<<< orphan*/  LRH_SC_VALUE ; 
 scalar_t__ NUM_MAP_ENTRIES ; 
 int /*<<< orphan*/  QPN_SELECT_OFFSET ; 
 unsigned int RCV_RSM_MAP_TABLE_RCV_CONTEXT_A_MASK ; 
 int /*<<< orphan*/  RSM_INS_VERBS ; 
 int /*<<< orphan*/  add_rsm_rule (struct hfi1_devdata*,int /*<<< orphan*/ ,struct rsm_rule_data*) ; 
 int /*<<< orphan*/  init_qpmap_table (struct hfi1_devdata*,unsigned int,unsigned int) ; 
 unsigned int* krcvqs ; 
 unsigned int num_vls ; 
 unsigned int qos_rmt_entries (struct hfi1_devdata*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void init_qos(struct hfi1_devdata *dd, struct rsm_map_table *rmt)
{
	struct rsm_rule_data rrd;
	unsigned qpns_per_vl, ctxt, i, qpn, n = 1, m;
	unsigned int rmt_entries;
	u64 reg;

	if (!rmt)
		goto bail;
	rmt_entries = qos_rmt_entries(dd, &m, &n);
	if (rmt_entries == 0)
		goto bail;
	qpns_per_vl = 1 << m;

	/* enough room in the map table? */
	rmt_entries = 1 << (m + n);
	if (rmt->used + rmt_entries >= NUM_MAP_ENTRIES)
		goto bail;

	/* add qos entries to the the RSM map table */
	for (i = 0, ctxt = FIRST_KERNEL_KCTXT; i < num_vls; i++) {
		unsigned tctxt;

		for (qpn = 0, tctxt = ctxt;
		     krcvqs[i] && qpn < qpns_per_vl; qpn++) {
			unsigned idx, regoff, regidx;

			/* generate the index the hardware will produce */
			idx = rmt->used + ((qpn << n) ^ i);
			regoff = (idx % 8) * 8;
			regidx = idx / 8;
			/* replace default with context number */
			reg = rmt->map[regidx];
			reg &= ~(RCV_RSM_MAP_TABLE_RCV_CONTEXT_A_MASK
				<< regoff);
			reg |= (u64)(tctxt++) << regoff;
			rmt->map[regidx] = reg;
			if (tctxt == ctxt + krcvqs[i])
				tctxt = ctxt;
		}
		ctxt += krcvqs[i];
	}

	rrd.offset = rmt->used;
	rrd.pkt_type = 2;
	rrd.field1_off = LRH_BTH_MATCH_OFFSET;
	rrd.field2_off = LRH_SC_MATCH_OFFSET;
	rrd.index1_off = LRH_SC_SELECT_OFFSET;
	rrd.index1_width = n;
	rrd.index2_off = QPN_SELECT_OFFSET;
	rrd.index2_width = m + n;
	rrd.mask1 = LRH_BTH_MASK;
	rrd.value1 = LRH_BTH_VALUE;
	rrd.mask2 = LRH_SC_MASK;
	rrd.value2 = LRH_SC_VALUE;

	/* add rule 0 */
	add_rsm_rule(dd, RSM_INS_VERBS, &rrd);

	/* mark RSM map entries as used */
	rmt->used += rmt_entries;
	/* map everything else to the mcast/err/vl15 context */
	init_qpmap_table(dd, HFI1_CTRL_CTXT, HFI1_CTRL_CTXT);
	dd->qos_shift = n + 1;
	return;
bail:
	dd->qos_shift = 1;
	init_qpmap_table(dd, FIRST_KERNEL_KCTXT, dd->n_krcv_queues - 1);
}