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
struct qedf_ioreq {int /*<<< orphan*/  tm_done; int /*<<< orphan*/ * sc_cmd; int /*<<< orphan*/  flags; } ;
struct qedf_ctx {int dummy; } ;
struct fcoe_cqe_rsp_info {int dummy; } ;
struct TYPE_2__ {struct fcoe_cqe_rsp_info rsp_info; } ;
struct fcoe_cqe {TYPE_1__ cqe_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_parse_fcp_rsp (struct qedf_ioreq*,struct fcoe_cqe_rsp_info*) ; 

void qedf_process_tmf_compl(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *io_req)
{
	struct fcoe_cqe_rsp_info *fcp_rsp;

	clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

	fcp_rsp = &cqe->cqe_info.rsp_info;
	qedf_parse_fcp_rsp(io_req, fcp_rsp);

	io_req->sc_cmd = NULL;
	complete(&io_req->tm_done);
}