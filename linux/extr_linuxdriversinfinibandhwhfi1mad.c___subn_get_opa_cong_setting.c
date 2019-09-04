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
struct opa_smp {int /*<<< orphan*/  status; } ;
struct opa_congestion_setting_entry_shadow {int /*<<< orphan*/  ccti_min; int /*<<< orphan*/  trigger_threshold; int /*<<< orphan*/  ccti_timer; int /*<<< orphan*/  ccti_increase; } ;
struct opa_congestion_setting_attr {TYPE_2__* entries; int /*<<< orphan*/  control_map; void* port_control; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_ibport {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  control_map; int /*<<< orphan*/  port_control; struct opa_congestion_setting_entry_shadow* entries; } ;
struct cc_state {TYPE_1__ cong_setting; } ;
struct TYPE_4__ {int /*<<< orphan*/  ccti_min; int /*<<< orphan*/  trigger_threshold; void* ccti_timer; int /*<<< orphan*/  ccti_increase; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_MAX_SLS ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct cc_state* get_cc_state (struct hfi1_pportdata*) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __subn_get_opa_cong_setting(struct opa_smp *smp, u32 am,
				       u8 *data, struct ib_device *ibdev,
				       u8 port, u32 *resp_len, u32 max_len)
{
	int i;
	struct opa_congestion_setting_attr *p =
		(struct opa_congestion_setting_attr *)data;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	struct opa_congestion_setting_entry_shadow *entries;
	struct cc_state *cc_state;

	if (smp_length_check(sizeof(*p), max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	rcu_read_lock();

	cc_state = get_cc_state(ppd);

	if (!cc_state) {
		rcu_read_unlock();
		return reply((struct ib_mad_hdr *)smp);
	}

	entries = cc_state->cong_setting.entries;
	p->port_control = cpu_to_be16(cc_state->cong_setting.port_control);
	p->control_map = cpu_to_be32(cc_state->cong_setting.control_map);
	for (i = 0; i < OPA_MAX_SLS; i++) {
		p->entries[i].ccti_increase = entries[i].ccti_increase;
		p->entries[i].ccti_timer = cpu_to_be16(entries[i].ccti_timer);
		p->entries[i].trigger_threshold =
			entries[i].trigger_threshold;
		p->entries[i].ccti_min = entries[i].ccti_min;
	}

	rcu_read_unlock();

	if (resp_len)
		*resp_len += sizeof(*p);

	return reply((struct ib_mad_hdr *)smp);
}