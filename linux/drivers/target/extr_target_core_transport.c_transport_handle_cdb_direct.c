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
struct se_cmd {int /*<<< orphan*/  transport_state; int /*<<< orphan*/  t_state; int /*<<< orphan*/  se_lun; } ;
typedef  scalar_t__ sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_T_ACTIVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  TRANSPORT_NEW_CMD ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ transport_generic_new_cmd (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_generic_request_failure (struct se_cmd*,scalar_t__) ; 

int transport_handle_cdb_direct(
	struct se_cmd *cmd)
{
	sense_reason_t ret;

	if (!cmd->se_lun) {
		dump_stack();
		pr_err("cmd->se_lun is NULL\n");
		return -EINVAL;
	}
	if (in_interrupt()) {
		dump_stack();
		pr_err("transport_generic_handle_cdb cannot be called"
				" from interrupt context\n");
		return -EINVAL;
	}
	/*
	 * Set TRANSPORT_NEW_CMD state and CMD_T_ACTIVE to ensure that
	 * outstanding descriptors are handled correctly during shutdown via
	 * transport_wait_for_tasks()
	 *
	 * Also, we don't take cmd->t_state_lock here as we only expect
	 * this to be called for initial descriptor submission.
	 */
	cmd->t_state = TRANSPORT_NEW_CMD;
	cmd->transport_state |= CMD_T_ACTIVE;

	/*
	 * transport_generic_new_cmd() is already handling QUEUE_FULL,
	 * so follow TRANSPORT_NEW_CMD processing thread context usage
	 * and call transport_generic_request_failure() if necessary..
	 */
	ret = transport_generic_new_cmd(cmd);
	if (ret)
		transport_generic_request_failure(cmd, ret);
	return 0;
}