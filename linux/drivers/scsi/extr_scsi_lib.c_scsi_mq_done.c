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
struct scsi_cmnd {int /*<<< orphan*/  state; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCMD_STATE_COMPLETE ; 
 int /*<<< orphan*/  blk_mq_complete_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_scsi_dispatch_cmd_done (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void scsi_mq_done(struct scsi_cmnd *cmd)
{
	if (unlikely(test_and_set_bit(SCMD_STATE_COMPLETE, &cmd->state)))
		return;
	trace_scsi_dispatch_cmd_done(cmd);

	/*
	 * If the block layer didn't complete the request due to a timeout
	 * injection, scsi must clear its internal completed state so that the
	 * timeout handler will see it needs to escalate its own error
	 * recovery.
	 */
	if (unlikely(!blk_mq_complete_request(cmd->request)))
		clear_bit(SCMD_STATE_COMPLETE, &cmd->state);
}