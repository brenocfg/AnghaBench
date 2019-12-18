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
struct TYPE_2__ {scalar_t__ cfg; int /*<<< orphan*/  sqs_count; int /*<<< orphan*/  num; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ qs; } ;
struct queue_set {int enable; int /*<<< orphan*/  vnic_id; } ;
struct qs_cfg {int ena; int be; int send_tstmp_ena; int /*<<< orphan*/  vnic; } ;
struct nicvf {scalar_t__ ptp_clock; int /*<<< orphan*/  sqs_count; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  netdev; struct queue_set* qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_QS_CFG ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

void nicvf_qset_config(struct nicvf *nic, bool enable)
{
	union nic_mbx mbx = {};
	struct queue_set *qs = nic->qs;
	struct qs_cfg *qs_cfg;

	if (!qs) {
		netdev_warn(nic->netdev,
			    "Qset is still not allocated, don't init queues\n");
		return;
	}

	qs->enable = enable;
	qs->vnic_id = nic->vf_id;

	/* Send a mailbox msg to PF to config Qset */
	mbx.qs.msg = NIC_MBOX_MSG_QS_CFG;
	mbx.qs.num = qs->vnic_id;
	mbx.qs.sqs_count = nic->sqs_count;

	mbx.qs.cfg = 0;
	qs_cfg = (struct qs_cfg *)&mbx.qs.cfg;
	if (qs->enable) {
		qs_cfg->ena = 1;
#ifdef __BIG_ENDIAN
		qs_cfg->be = 1;
#endif
		qs_cfg->vnic = qs->vnic_id;
		/* Enable Tx timestamping capability */
		if (nic->ptp_clock)
			qs_cfg->send_tstmp_ena = 1;
	}
	nicvf_send_msg_to_pf(nic, &mbx);
}