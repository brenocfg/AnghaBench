#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cc_table_entry_shadow {int /*<<< orphan*/  entry; } ;
struct ib_cc_table_attr {TYPE_2__* ccti_entries; void* ccti_limit; } ;
struct hfi1_pportdata {int cc_max_table_entries; } ;
struct hfi1_ibport {int dummy; } ;
struct TYPE_3__ {struct ib_cc_table_entry_shadow* entries; int /*<<< orphan*/  ccti_limit; } ;
struct cc_state {TYPE_1__ cct; } ;
struct TYPE_4__ {void* entry; } ;

/* Variables and functions */
 int IB_CCT_ENTRIES ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NBLK (int) ; 
 int OPA_AM_START_BLK (int) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct cc_state* get_cc_state (struct hfi1_pportdata*) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __subn_get_opa_cc_table(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len, u32 max_len)
{
	struct ib_cc_table_attr *cc_table_attr =
		(struct ib_cc_table_attr *)data;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 start_block = OPA_AM_START_BLK(am);
	u32 n_blocks = OPA_AM_NBLK(am);
	struct ib_cc_table_entry_shadow *entries;
	int i, j;
	u32 sentry, eentry;
	struct cc_state *cc_state;
	u32 size = sizeof(u16) * (IB_CCT_ENTRIES * n_blocks + 1);

	/* sanity check n_blocks, start_block */
	if (n_blocks == 0 || smp_length_check(size, max_len) ||
	    start_block + n_blocks > ppd->cc_max_table_entries) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	rcu_read_lock();

	cc_state = get_cc_state(ppd);

	if (!cc_state) {
		rcu_read_unlock();
		return reply((struct ib_mad_hdr *)smp);
	}

	sentry = start_block * IB_CCT_ENTRIES;
	eentry = sentry + (IB_CCT_ENTRIES * n_blocks);

	cc_table_attr->ccti_limit = cpu_to_be16(cc_state->cct.ccti_limit);

	entries = cc_state->cct.entries;

	/* return n_blocks, though the last block may not be full */
	for (j = 0, i = sentry; i < eentry; j++, i++)
		cc_table_attr->ccti_entries[j].entry =
			cpu_to_be16(entries[i].entry);

	rcu_read_unlock();

	if (resp_len)
		*resp_len += size;

	return reply((struct ib_mad_hdr *)smp);
}