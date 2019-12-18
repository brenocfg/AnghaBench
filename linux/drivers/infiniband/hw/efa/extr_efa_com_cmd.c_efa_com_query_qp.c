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
struct efa_com_query_qp_result {int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  sq_draining; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_state; } ;
struct efa_com_query_qp_params {int /*<<< orphan*/  qp_handle; } ;
struct efa_com_admin_queue {int dummy; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; struct efa_com_admin_queue aq; } ;
struct efa_admin_query_qp_resp {int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  sq_draining; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct efa_admin_query_qp_cmd {int /*<<< orphan*/  qp_handle; TYPE_1__ aq_common_desc; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_QUERY_QP ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int efa_com_query_qp(struct efa_com_dev *edev,
		     struct efa_com_query_qp_params *params,
		     struct efa_com_query_qp_result *result)
{
	struct efa_com_admin_queue *aq = &edev->aq;
	struct efa_admin_query_qp_cmd cmd = {};
	struct efa_admin_query_qp_resp resp;
	int err;

	cmd.aq_common_desc.opcode = EFA_ADMIN_QUERY_QP;
	cmd.qp_handle = params->qp_handle;

	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)&cmd,
			       sizeof(cmd),
			       (struct efa_admin_acq_entry *)&resp,
			       sizeof(resp));
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to query qp-%u [%d]\n",
				      cmd.qp_handle, err);
		return err;
	}

	result->qp_state = resp.qp_state;
	result->qkey = resp.qkey;
	result->sq_draining = resp.sq_draining;
	result->sq_psn = resp.sq_psn;

	return 0;
}