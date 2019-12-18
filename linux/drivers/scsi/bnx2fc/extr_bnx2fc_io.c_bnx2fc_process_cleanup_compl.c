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
typedef  int /*<<< orphan*/  u8 ;
struct fcoe_task_ctx_entry {int dummy; } ;
struct bnx2fc_cmd {int /*<<< orphan*/  cleanup_done; scalar_t__ wait_for_cleanup_comp; int /*<<< orphan*/  refcount; int /*<<< orphan*/  abts_done; scalar_t__ wait_for_abts_comp; int /*<<< orphan*/  req_flags; int /*<<< orphan*/  cmd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_FLAG_ABTS_DONE ; 
 int /*<<< orphan*/  BNX2FC_FLAG_ISSUE_ABTS ; 
 int /*<<< orphan*/  BNX2FC_FLAG_ISSUE_CLEANUP_REQ ; 
 int /*<<< orphan*/  BNX2FC_IO_DBG (struct bnx2fc_cmd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  bnx2fc_cmd_release ; 
 int /*<<< orphan*/  bnx2fc_scsi_done (struct bnx2fc_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnx2fc_process_cleanup_compl(struct bnx2fc_cmd *io_req,
				  struct fcoe_task_ctx_entry *task,
				  u8 num_rq)
{
	BNX2FC_IO_DBG(io_req, "Entered process_cleanup_compl "
			      "refcnt = %d, cmd_type = %d\n",
		   kref_read(&io_req->refcount), io_req->cmd_type);
	/*
	 * Test whether there is a cleanup request pending. If not just
	 * exit.
	 */
	if (!test_and_clear_bit(BNX2FC_FLAG_ISSUE_CLEANUP_REQ,
				&io_req->req_flags))
		return;
	/*
	 * If we receive a cleanup completion for this request then the
	 * firmware will not give us an abort completion for this request
	 * so clear any ABTS pending flags.
	 */
	if (test_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags) &&
	    !test_bit(BNX2FC_FLAG_ABTS_DONE, &io_req->req_flags)) {
		set_bit(BNX2FC_FLAG_ABTS_DONE, &io_req->req_flags);
		if (io_req->wait_for_abts_comp)
			complete(&io_req->abts_done);
	}

	bnx2fc_scsi_done(io_req, DID_ERROR);
	kref_put(&io_req->refcount, bnx2fc_cmd_release);
	if (io_req->wait_for_cleanup_comp)
		complete(&io_req->cleanup_done);
}