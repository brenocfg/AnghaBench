#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qedf_ioreq {int /*<<< orphan*/  cleanup_done; int /*<<< orphan*/  flags; int /*<<< orphan*/  xid; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct fcoe_cqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_CMD_IN_CLEANUP ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void qedf_process_cleanup_compl(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *io_req)
{
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO, "Entered xid = 0x%x\n",
		   io_req->xid);

	clear_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags);

	/* Complete so we can finish cleaning up the I/O */
	complete(&io_req->cleanup_done);
}