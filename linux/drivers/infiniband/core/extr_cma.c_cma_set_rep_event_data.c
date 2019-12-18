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
struct TYPE_3__ {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  private_data_len; void* private_data; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct rdma_cm_event {TYPE_2__ param; } ;
struct ib_cm_rep_event_param {int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CM_REP_PRIVATE_DATA_SIZE ; 

__attribute__((used)) static void cma_set_rep_event_data(struct rdma_cm_event *event,
				   const struct ib_cm_rep_event_param *rep_data,
				   void *private_data)
{
	event->param.conn.private_data = private_data;
	event->param.conn.private_data_len = IB_CM_REP_PRIVATE_DATA_SIZE;
	event->param.conn.responder_resources = rep_data->responder_resources;
	event->param.conn.initiator_depth = rep_data->initiator_depth;
	event->param.conn.flow_control = rep_data->flow_control;
	event->param.conn.rnr_retry_count = rep_data->rnr_retry_count;
	event->param.conn.srq = rep_data->srq;
	event->param.conn.qp_num = rep_data->remote_qpn;
}