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
struct qib_pportdata {int /*<<< orphan*/  cc_shadow_lock; TYPE_1__* congestion_entries_shadow; } ;
struct qib_ibport {int dummy; } ;
struct ib_smp {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cc_mad {scalar_t__ mgmt_data; } ;
struct ib_cc_congestion_setting_attr {TYPE_2__* entries; void* control_map; void* port_control; } ;
struct ib_cc_congestion_entry_shadow {int /*<<< orphan*/  ccti_min; int /*<<< orphan*/  trigger_threshold; int /*<<< orphan*/  ccti_timer; int /*<<< orphan*/  ccti_increase; } ;
struct TYPE_4__ {int /*<<< orphan*/  ccti_min; int /*<<< orphan*/  trigger_threshold; void* ccti_timer; int /*<<< orphan*/  ccti_increase; } ;
struct TYPE_3__ {int /*<<< orphan*/  control_map; int /*<<< orphan*/  port_control; struct ib_cc_congestion_entry_shadow* entries; } ;

/* Variables and functions */
 int IB_CC_CCS_ENTRIES ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int reply (struct ib_smp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_get_congestion_setting(struct ib_cc_mad *ccp,
				struct ib_device *ibdev, u8 port)
{
	int i;
	struct ib_cc_congestion_setting_attr *p =
		(struct ib_cc_congestion_setting_attr *)ccp->mgmt_data;
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	struct ib_cc_congestion_entry_shadow *entries;

	memset(ccp->mgmt_data, 0, sizeof(ccp->mgmt_data));

	spin_lock(&ppd->cc_shadow_lock);

	entries = ppd->congestion_entries_shadow->entries;
	p->port_control = cpu_to_be16(
		ppd->congestion_entries_shadow->port_control);
	p->control_map = cpu_to_be16(
		ppd->congestion_entries_shadow->control_map);
	for (i = 0; i < IB_CC_CCS_ENTRIES; i++) {
		p->entries[i].ccti_increase = entries[i].ccti_increase;
		p->entries[i].ccti_timer = cpu_to_be16(entries[i].ccti_timer);
		p->entries[i].trigger_threshold = entries[i].trigger_threshold;
		p->entries[i].ccti_min = entries[i].ccti_min;
	}

	spin_unlock(&ppd->cc_shadow_lock);

	return reply((struct ib_smp *) ccp);
}