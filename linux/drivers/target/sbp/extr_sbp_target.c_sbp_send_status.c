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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct sbp_target_request {int orb_pointer; int /*<<< orphan*/  se_cmd; TYPE_1__ status; struct sbp_login_descriptor* login; } ;
struct sbp_login_descriptor {int /*<<< orphan*/  status_fifo_addr; } ;

/* Variables and functions */
 int EIO ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int sbp_run_request_transaction (struct sbp_target_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  target_put_sess_cmd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sbp_send_status(struct sbp_target_request *req)
{
	int rc, ret = 0, length;
	struct sbp_login_descriptor *login = req->login;

	length = (((be32_to_cpu(req->status.status) >> 24) & 0x07) + 1) * 4;

	rc = sbp_run_request_transaction(req, TCODE_WRITE_BLOCK_REQUEST,
			login->status_fifo_addr, &req->status, length);
	if (rc != RCODE_COMPLETE) {
		pr_debug("sbp_send_status: write failed: 0x%x\n", rc);
		ret = -EIO;
		goto put_ref;
	}

	pr_debug("sbp_send_status: status write complete for ORB: 0x%llx\n",
			req->orb_pointer);
	/*
	 * Drop the extra ACK_KREF reference taken by target_submit_cmd()
	 * ahead of sbp_check_stop_free() -> transport_generic_free_cmd()
	 * final se_cmd->cmd_kref put.
	 */
put_ref:
	target_put_sess_cmd(&req->se_cmd);
	return ret;
}