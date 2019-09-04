#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ib_cm_rep_param {int srq; scalar_t__ private_data_len; scalar_t__ private_data; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  failover_accepted; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  starting_psn; } ;
struct cm_rep_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  local_ca_guid; int /*<<< orphan*/  resp_resources; int /*<<< orphan*/  remote_comm_id; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  hdr; } ;
struct TYPE_10__ {TYPE_4__* device; int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct TYPE_8__ {TYPE_2__* port; } ;
struct cm_id_private {scalar_t__ qp_type; TYPE_5__ id; TYPE_3__ av; int /*<<< orphan*/  tid; } ;
struct TYPE_9__ {int /*<<< orphan*/  node_guid; } ;
struct TYPE_7__ {TYPE_1__* cm_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  ack_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_REP_ATTR_ID ; 
 scalar_t__ IB_QPT_XRC_TGT ; 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_set_failover (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_set_flow_ctrl (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_set_local_eecn (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_set_local_qpn (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_set_rnr_retry_count (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_set_srq (struct cm_rep_msg*,int) ; 
 int /*<<< orphan*/  cm_rep_set_starting_psn (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rep_set_target_ack_delay (struct cm_rep_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void cm_format_rep(struct cm_rep_msg *rep_msg,
			  struct cm_id_private *cm_id_priv,
			  struct ib_cm_rep_param *param)
{
	cm_format_mad_hdr(&rep_msg->hdr, CM_REP_ATTR_ID, cm_id_priv->tid);
	rep_msg->local_comm_id = cm_id_priv->id.local_id;
	rep_msg->remote_comm_id = cm_id_priv->id.remote_id;
	cm_rep_set_starting_psn(rep_msg, cpu_to_be32(param->starting_psn));
	rep_msg->resp_resources = param->responder_resources;
	cm_rep_set_target_ack_delay(rep_msg,
				    cm_id_priv->av.port->cm_dev->ack_delay);
	cm_rep_set_failover(rep_msg, param->failover_accepted);
	cm_rep_set_rnr_retry_count(rep_msg, param->rnr_retry_count);
	rep_msg->local_ca_guid = cm_id_priv->id.device->node_guid;

	if (cm_id_priv->qp_type != IB_QPT_XRC_TGT) {
		rep_msg->initiator_depth = param->initiator_depth;
		cm_rep_set_flow_ctrl(rep_msg, param->flow_control);
		cm_rep_set_srq(rep_msg, param->srq);
		cm_rep_set_local_qpn(rep_msg, cpu_to_be32(param->qp_num));
	} else {
		cm_rep_set_srq(rep_msg, 1);
		cm_rep_set_local_eecn(rep_msg, cpu_to_be32(param->qp_num));
	}

	if (param->private_data && param->private_data_len)
		memcpy(rep_msg->private_data, param->private_data,
		       param->private_data_len);
}