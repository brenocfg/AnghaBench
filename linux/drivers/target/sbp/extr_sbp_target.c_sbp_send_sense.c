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
struct se_cmd {scalar_t__ scsi_sense_length; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct sbp_target_request {TYPE_1__ status; struct se_cmd se_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP_STATUS_OK ; 
 int STATUS_BLOCK_DEAD (int /*<<< orphan*/ ) ; 
 int STATUS_BLOCK_LEN (int) ; 
 int STATUS_BLOCK_RESP (int /*<<< orphan*/ ) ; 
 int STATUS_BLOCK_SBP_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_RESP_REQUEST_COMPLETE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int sbp_send_status (struct sbp_target_request*) ; 
 int /*<<< orphan*/  sbp_sense_mangle (struct sbp_target_request*) ; 

__attribute__((used)) static int sbp_send_sense(struct sbp_target_request *req)
{
	struct se_cmd *se_cmd = &req->se_cmd;

	if (se_cmd->scsi_sense_length) {
		sbp_sense_mangle(req);
	} else {
		req->status.status |= cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_DEAD(0) |
			STATUS_BLOCK_LEN(1) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
	}

	return sbp_send_status(req);
}