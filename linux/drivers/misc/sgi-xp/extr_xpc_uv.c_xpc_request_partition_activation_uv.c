#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  activate_gru_mq_desc_gpa; int /*<<< orphan*/  heartbeat_gpa; } ;
struct TYPE_10__ {TYPE_1__ uv; } ;
struct xpc_rsvd_page {short SAL_partid; TYPE_2__ sn; int /*<<< orphan*/  ts_jiffies; } ;
struct TYPE_11__ {scalar_t__ remote_act_state; int /*<<< orphan*/  activate_gru_mq_desc_gpa; int /*<<< orphan*/  heartbeat_gpa; } ;
struct TYPE_12__ {TYPE_3__ uv; } ;
struct xpc_partition {unsigned long remote_rp_pa; scalar_t__ act_state; TYPE_4__ sn; int /*<<< orphan*/  remote_rp_ts_jiffies; } ;
struct xpc_activate_mq_msg_activate_req_uv {int /*<<< orphan*/  activate_gru_mq_desc_gpa; int /*<<< orphan*/  heartbeat_gpa; int /*<<< orphan*/  rp_gpa; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_13__ {int /*<<< orphan*/  activate_gru_mq_desc_gpa; int /*<<< orphan*/  heartbeat_gpa; } ;
struct TYPE_14__ {TYPE_5__ uv; } ;
struct TYPE_15__ {TYPE_6__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_ACTIVATE_MQ_MSG_ACTIVATE_REQ_UV ; 
 int /*<<< orphan*/  XPC_P_ASR_ACTIVATE_UV ; 
 scalar_t__ XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  uv_gpa (TYPE_7__*) ; 
 struct xpc_partition* xpc_partitions ; 
 TYPE_7__* xpc_rsvd_page ; 
 int /*<<< orphan*/  xpc_send_activate_IRQ_part_uv (struct xpc_partition*,struct xpc_activate_mq_msg_activate_req_uv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_send_local_activate_IRQ_uv (struct xpc_partition*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_request_partition_activation_uv(struct xpc_rsvd_page *remote_rp,
				    unsigned long remote_rp_gpa, int nasid)
{
	short partid = remote_rp->SAL_partid;
	struct xpc_partition *part = &xpc_partitions[partid];
	struct xpc_activate_mq_msg_activate_req_uv msg;

	part->remote_rp_pa = remote_rp_gpa; /* !!! _pa here is really _gpa */
	part->remote_rp_ts_jiffies = remote_rp->ts_jiffies;
	part->sn.uv.heartbeat_gpa = remote_rp->sn.uv.heartbeat_gpa;
	part->sn.uv.activate_gru_mq_desc_gpa =
	    remote_rp->sn.uv.activate_gru_mq_desc_gpa;

	/*
	 * ??? Is it a good idea to make this conditional on what is
	 * ??? potentially stale state information?
	 */
	if (part->sn.uv.remote_act_state == XPC_P_AS_INACTIVE) {
		msg.rp_gpa = uv_gpa(xpc_rsvd_page);
		msg.heartbeat_gpa = xpc_rsvd_page->sn.uv.heartbeat_gpa;
		msg.activate_gru_mq_desc_gpa =
		    xpc_rsvd_page->sn.uv.activate_gru_mq_desc_gpa;
		xpc_send_activate_IRQ_part_uv(part, &msg, sizeof(msg),
					   XPC_ACTIVATE_MQ_MSG_ACTIVATE_REQ_UV);
	}

	if (part->act_state == XPC_P_AS_INACTIVE)
		xpc_send_local_activate_IRQ_uv(part, XPC_P_ASR_ACTIVATE_UV);
}