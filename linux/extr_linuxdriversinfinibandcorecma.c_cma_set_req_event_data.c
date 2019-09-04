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
struct TYPE_3__ {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; scalar_t__ private_data_len; void* private_data; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct rdma_cm_event {TYPE_2__ param; } ;
struct ib_cm_req_event_param {int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; } ;

/* Variables and functions */
 scalar_t__ IB_CM_REQ_PRIVATE_DATA_SIZE ; 

__attribute__((used)) static void cma_set_req_event_data(struct rdma_cm_event *event,
				   const struct ib_cm_req_event_param *req_data,
				   void *private_data, int offset)
{
	event->param.conn.private_data = private_data + offset;
	event->param.conn.private_data_len = IB_CM_REQ_PRIVATE_DATA_SIZE - offset;
	event->param.conn.responder_resources = req_data->responder_resources;
	event->param.conn.initiator_depth = req_data->initiator_depth;
	event->param.conn.flow_control = req_data->flow_control;
	event->param.conn.retry_count = req_data->retry_count;
	event->param.conn.rnr_retry_count = req_data->rnr_retry_count;
	event->param.conn.srq = req_data->srq;
	event->param.conn.qp_num = req_data->remote_qpn;
}