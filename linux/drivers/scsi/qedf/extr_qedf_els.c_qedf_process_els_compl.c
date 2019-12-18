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
struct TYPE_4__ {int /*<<< orphan*/  resp_len; } ;
struct qedf_ioreq {int /*<<< orphan*/  refcount; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/  (* cb_func ) (int /*<<< orphan*/ *) ;TYPE_2__ mp_req; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  xid; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct fcoe_cqe_midpath_info {int /*<<< orphan*/  data_placement_size; } ;
struct TYPE_3__ {struct fcoe_cqe_midpath_info midpath_info; } ;
struct fcoe_cqe {TYPE_1__ cqe_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void qedf_process_els_compl(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *els_req)
{
	struct fcoe_cqe_midpath_info *mp_info;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Entered with xid = 0x%x"
		   " cmd_type = %d.\n", els_req->xid, els_req->cmd_type);

	clear_bit(QEDF_CMD_OUTSTANDING, &els_req->flags);

	/* Kill the ELS timer */
	cancel_delayed_work(&els_req->timeout_work);

	/* Get ELS response length from CQE */
	mp_info = &cqe->cqe_info.midpath_info;
	els_req->mp_req.resp_len = mp_info->data_placement_size;

	/* Parse ELS response */
	if ((els_req->cb_func) && (els_req->cb_arg)) {
		els_req->cb_func(els_req->cb_arg);
		els_req->cb_arg = NULL;
	}

	kref_put(&els_req->refcount, qedf_release_cmd);
}