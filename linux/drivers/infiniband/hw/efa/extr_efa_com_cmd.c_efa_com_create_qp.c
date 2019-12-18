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
struct efa_com_admin_queue {int dummy; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; struct efa_com_admin_queue aq; } ;
struct efa_com_create_qp_result {int /*<<< orphan*/  recv_sub_cq_idx; int /*<<< orphan*/  send_sub_cq_idx; int /*<<< orphan*/  llq_descriptors_offset; int /*<<< orphan*/  rq_db_offset; int /*<<< orphan*/  sq_db_offset; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  qp_handle; } ;
struct efa_com_create_qp_params {int /*<<< orphan*/  uarn; int /*<<< orphan*/  rq_depth; int /*<<< orphan*/  rq_ring_size_in_bytes; int /*<<< orphan*/  sq_depth; int /*<<< orphan*/  sq_ring_size_in_bytes; int /*<<< orphan*/  recv_cq_idx; int /*<<< orphan*/  send_cq_idx; int /*<<< orphan*/  rq_base_addr; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  pd; } ;
struct efa_admin_create_qp_resp {int /*<<< orphan*/  recv_sub_cq_idx; int /*<<< orphan*/  send_sub_cq_idx; int /*<<< orphan*/  llq_descriptors_offset; int /*<<< orphan*/  rq_db_offset; int /*<<< orphan*/  sq_db_offset; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  qp_handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  recv_queue_depth; int /*<<< orphan*/  recv_queue_ring_size; int /*<<< orphan*/  send_queue_depth; int /*<<< orphan*/  send_queue_ring_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;
struct efa_admin_create_qp_cmd {int /*<<< orphan*/  uar; TYPE_2__ qp_alloc_size; int /*<<< orphan*/  recv_cq_idx; int /*<<< orphan*/  send_cq_idx; int /*<<< orphan*/  rq_base_addr; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  pd; TYPE_1__ aq_common_desc; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  create_qp_cmd ;
typedef  int /*<<< orphan*/  cmd_completion ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_CREATE_QP ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 

int efa_com_create_qp(struct efa_com_dev *edev,
		      struct efa_com_create_qp_params *params,
		      struct efa_com_create_qp_result *res)
{
	struct efa_admin_create_qp_cmd create_qp_cmd = {};
	struct efa_admin_create_qp_resp cmd_completion;
	struct efa_com_admin_queue *aq = &edev->aq;
	int err;

	create_qp_cmd.aq_common_desc.opcode = EFA_ADMIN_CREATE_QP;

	create_qp_cmd.pd = params->pd;
	create_qp_cmd.qp_type = params->qp_type;
	create_qp_cmd.rq_base_addr = params->rq_base_addr;
	create_qp_cmd.send_cq_idx = params->send_cq_idx;
	create_qp_cmd.recv_cq_idx = params->recv_cq_idx;
	create_qp_cmd.qp_alloc_size.send_queue_ring_size =
		params->sq_ring_size_in_bytes;
	create_qp_cmd.qp_alloc_size.send_queue_depth =
			params->sq_depth;
	create_qp_cmd.qp_alloc_size.recv_queue_ring_size =
			params->rq_ring_size_in_bytes;
	create_qp_cmd.qp_alloc_size.recv_queue_depth =
			params->rq_depth;
	create_qp_cmd.uar = params->uarn;

	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)&create_qp_cmd,
			       sizeof(create_qp_cmd),
			       (struct efa_admin_acq_entry *)&cmd_completion,
			       sizeof(cmd_completion));
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to create qp [%d]\n", err);
		return err;
	}

	res->qp_handle = cmd_completion.qp_handle;
	res->qp_num = cmd_completion.qp_num;
	res->sq_db_offset = cmd_completion.sq_db_offset;
	res->rq_db_offset = cmd_completion.rq_db_offset;
	res->llq_descriptors_offset = cmd_completion.llq_descriptors_offset;
	res->send_sub_cq_idx = cmd_completion.send_sub_cq_idx;
	res->recv_sub_cq_idx = cmd_completion.recv_sub_cq_idx;

	return 0;
}