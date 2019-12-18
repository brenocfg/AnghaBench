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
typedef  int u64 ;
typedef  int u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct opa_hfi1_cong_log_event_internal {int timestamp; int sl; int svc_type; int rlid; int /*<<< orphan*/  rqpn; int /*<<< orphan*/  lqpn; } ;
struct opa_hfi1_cong_log {TYPE_1__* events; void* current_time_stamp; int /*<<< orphan*/  threshold_cong_event_map; int /*<<< orphan*/  threshold_event_counter; scalar_t__ congestion_flags; int /*<<< orphan*/  log_type; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int cc_mad_idx; int /*<<< orphan*/  cc_log_lock; scalar_t__ threshold_event_counter; int /*<<< orphan*/ * threshold_cong_event_map; struct opa_hfi1_cong_log_event_internal* cc_events; } ;
struct hfi1_ibport {int dummy; } ;
struct TYPE_2__ {int sl_svc_type_cn_entry; void* timestamp_cn_entry; void* remote_lid_cn_entry; int /*<<< orphan*/  remote_qp_number_cn_entry; int /*<<< orphan*/  local_qp_cn_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  OPA_CC_LOG_TYPE_HFI ; 
 int OPA_CONG_LOG_ELEMS ; 
 int U32_MAX ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 void* cpu_to_be32 (int) ; 
 int ktime_get_ns () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __subn_get_opa_hfi1_cong_log(struct opa_smp *smp, u32 am,
					u8 *data, struct ib_device *ibdev,
					u8 port, u32 *resp_len, u32 max_len)
{
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	struct opa_hfi1_cong_log *cong_log = (struct opa_hfi1_cong_log *)data;
	u64 ts;
	int i;

	if (am || smp_length_check(sizeof(*cong_log), max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	spin_lock_irq(&ppd->cc_log_lock);

	cong_log->log_type = OPA_CC_LOG_TYPE_HFI;
	cong_log->congestion_flags = 0;
	cong_log->threshold_event_counter =
		cpu_to_be16(ppd->threshold_event_counter);
	memcpy(cong_log->threshold_cong_event_map,
	       ppd->threshold_cong_event_map,
	       sizeof(cong_log->threshold_cong_event_map));
	/* keep timestamp in units of 1.024 usec */
	ts = ktime_get_ns() / 1024;
	cong_log->current_time_stamp = cpu_to_be32(ts);
	for (i = 0; i < OPA_CONG_LOG_ELEMS; i++) {
		struct opa_hfi1_cong_log_event_internal *cce =
			&ppd->cc_events[ppd->cc_mad_idx++];
		if (ppd->cc_mad_idx == OPA_CONG_LOG_ELEMS)
			ppd->cc_mad_idx = 0;
		/*
		 * Entries which are older than twice the time
		 * required to wrap the counter are supposed to
		 * be zeroed (CA10-49 IBTA, release 1.2.1, V1).
		 */
		if ((ts - cce->timestamp) / 2 > U32_MAX)
			continue;
		memcpy(cong_log->events[i].local_qp_cn_entry, &cce->lqpn, 3);
		memcpy(cong_log->events[i].remote_qp_number_cn_entry,
		       &cce->rqpn, 3);
		cong_log->events[i].sl_svc_type_cn_entry =
			((cce->sl & 0x1f) << 3) | (cce->svc_type & 0x7);
		cong_log->events[i].remote_lid_cn_entry =
			cpu_to_be32(cce->rlid);
		cong_log->events[i].timestamp_cn_entry =
			cpu_to_be32(cce->timestamp);
	}

	/*
	 * Reset threshold_cong_event_map, and threshold_event_counter
	 * to 0 when log is read.
	 */
	memset(ppd->threshold_cong_event_map, 0x0,
	       sizeof(ppd->threshold_cong_event_map));
	ppd->threshold_event_counter = 0;

	spin_unlock_irq(&ppd->cc_log_lock);

	if (resp_len)
		*resp_len += sizeof(struct opa_hfi1_cong_log);

	return reply((struct ib_mad_hdr *)smp);
}