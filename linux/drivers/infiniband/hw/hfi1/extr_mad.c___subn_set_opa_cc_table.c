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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cc_table_entry_shadow {int entry; } ;
struct ib_cc_table_attr {TYPE_1__* ccti_entries; int /*<<< orphan*/  ccti_limit; } ;
struct hfi1_pportdata {int cc_max_table_entries; int total_cct_entry; int /*<<< orphan*/  cc_state_lock; struct ib_cc_table_entry_shadow* ccti_entries; } ;
struct hfi1_ibport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int IB_CCT_ENTRIES ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NBLK (int) ; 
 int OPA_AM_START_BLK (int) ; 
 int __subn_get_opa_cc_table (struct opa_smp*,int,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  apply_cc_state (struct hfi1_pportdata*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __subn_set_opa_cc_table(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len, u32 max_len)
{
	struct ib_cc_table_attr *p = (struct ib_cc_table_attr *)data;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 start_block = OPA_AM_START_BLK(am);
	u32 n_blocks = OPA_AM_NBLK(am);
	struct ib_cc_table_entry_shadow *entries;
	int i, j;
	u32 sentry, eentry;
	u16 ccti_limit;
	u32 size = sizeof(u16) * (IB_CCT_ENTRIES * n_blocks + 1);

	/* sanity check n_blocks, start_block */
	if (n_blocks == 0 || smp_length_check(size, max_len) ||
	    start_block + n_blocks > ppd->cc_max_table_entries) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	sentry = start_block * IB_CCT_ENTRIES;
	eentry = sentry + ((n_blocks - 1) * IB_CCT_ENTRIES) +
		 (be16_to_cpu(p->ccti_limit)) % IB_CCT_ENTRIES + 1;

	/* sanity check ccti_limit */
	ccti_limit = be16_to_cpu(p->ccti_limit);
	if (ccti_limit + 1 > eentry) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	/*
	 * Save details from packet into the ppd.  Hold the cc_state_lock so
	 * our information is consistent with anyone trying to apply the state.
	 */
	spin_lock(&ppd->cc_state_lock);
	ppd->total_cct_entry = ccti_limit + 1;
	entries = ppd->ccti_entries;
	for (j = 0, i = sentry; i < eentry; j++, i++)
		entries[i].entry = be16_to_cpu(p->ccti_entries[j].entry);
	spin_unlock(&ppd->cc_state_lock);

	/* now apply the information */
	apply_cc_state(ppd);

	return __subn_get_opa_cc_table(smp, am, data, ibdev, port, resp_len,
				       max_len);
}