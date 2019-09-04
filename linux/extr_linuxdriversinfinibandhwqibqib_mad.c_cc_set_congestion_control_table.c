#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qib_pportdata {int total_cct_entry; int cc_supported_table_entries; int ccti_limit; int /*<<< orphan*/  cc_shadow_lock; struct ib_cc_table_entry_shadow* congestion_entries; TYPE_3__* congestion_entries_shadow; int /*<<< orphan*/  cc_sl_control_map; struct ib_cc_table_entry_shadow* ccti_entries; TYPE_2__* ccti_entries_shadow; } ;
struct qib_ibport {int dummy; } ;
struct ib_smp {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cc_table_entry_shadow {int entry; } ;
struct ib_cc_table_entry {int dummy; } ;
struct ib_cc_table_attr {TYPE_1__* ccti_entries; int /*<<< orphan*/  ccti_limit; } ;
struct ib_cc_mad {int /*<<< orphan*/  attr_mod; scalar_t__ mgmt_data; } ;
struct ib_cc_congestion_entry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  control_map; int /*<<< orphan*/  port_control; } ;
struct TYPE_5__ {int ccti_last_entry; int /*<<< orphan*/  entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int IB_CCT_ENTRIES ; 
 int IB_CC_CCS_ENTRIES ; 
 int /*<<< orphan*/  IB_CC_CCS_PC_SL_BASED ; 
 int IB_CC_TABLE_CAP_DEFAULT ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ib_cc_table_entry_shadow*,int) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int reply (struct ib_smp*) ; 
 int reply_failure (struct ib_smp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_set_congestion_control_table(struct ib_cc_mad *ccp,
				struct ib_device *ibdev, u8 port)
{
	struct ib_cc_table_attr *p =
		(struct ib_cc_table_attr *)ccp->mgmt_data;
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	u32 cct_block_index = be32_to_cpu(ccp->attr_mod);
	u32 cct_entry;
	struct ib_cc_table_entry_shadow *entries;
	int i;

	/* Is the table index more than what is supported? */
	if (cct_block_index > IB_CC_TABLE_CAP_DEFAULT - 1)
		goto bail;

	/* If this packet is the first in the sequence then
	 * zero the total table entry count.
	 */
	if (be16_to_cpu(p->ccti_limit) < IB_CCT_ENTRIES)
		ppd->total_cct_entry = 0;

	cct_entry = (be16_to_cpu(p->ccti_limit))%IB_CCT_ENTRIES;

	/* ccti_limit is 0 to 63 */
	ppd->total_cct_entry += (cct_entry + 1);

	if (ppd->total_cct_entry > ppd->cc_supported_table_entries)
		goto bail;

	ppd->ccti_limit = be16_to_cpu(p->ccti_limit);

	entries = ppd->ccti_entries + (IB_CCT_ENTRIES * cct_block_index);

	for (i = 0; i <= cct_entry; i++)
		entries[i].entry = be16_to_cpu(p->ccti_entries[i].entry);

	spin_lock(&ppd->cc_shadow_lock);

	ppd->ccti_entries_shadow->ccti_last_entry = ppd->total_cct_entry - 1;
	memcpy(ppd->ccti_entries_shadow->entries, ppd->ccti_entries,
		(ppd->total_cct_entry * sizeof(struct ib_cc_table_entry)));

	ppd->congestion_entries_shadow->port_control = IB_CC_CCS_PC_SL_BASED;
	ppd->congestion_entries_shadow->control_map = ppd->cc_sl_control_map;
	memcpy(ppd->congestion_entries_shadow->entries, ppd->congestion_entries,
		IB_CC_CCS_ENTRIES * sizeof(struct ib_cc_congestion_entry));

	spin_unlock(&ppd->cc_shadow_lock);

	return reply((struct ib_smp *) ccp);

bail:
	return reply_failure((struct ib_smp *) ccp);
}