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
struct TYPE_2__ {int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct queue_set {int dummy; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_RQ_SW_SYNC ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void nicvf_reclaim_rcv_queue(struct nicvf *nic,
				    struct queue_set *qs, int qidx)
{
	union nic_mbx mbx = {};

	/* Make sure all packets in the pipeline are written back into mem */
	mbx.msg.msg = NIC_MBOX_MSG_RQ_SW_SYNC;
	nicvf_send_msg_to_pf(nic, &mbx);
}