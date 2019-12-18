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
struct msrl_action {long err; struct isst_if_mbox_cmd* mbox_cmd; } ;
struct isst_if_mbox_cmd {int /*<<< orphan*/  req_data; int /*<<< orphan*/  parameter; int /*<<< orphan*/  logical_cpu; int /*<<< orphan*/  sub_command; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EINVAL ; 
 long EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ isst_if_mbox_cmd_invalid (struct isst_if_mbox_cmd*) ; 
 scalar_t__ isst_if_mbox_cmd_set_req (struct isst_if_mbox_cmd*) ; 
 long isst_store_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msrl_update_func ; 
 int smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msrl_action*,int) ; 

__attribute__((used)) static long isst_if_mbox_proc_cmd(u8 *cmd_ptr, int *write_only, int resume)
{
	struct msrl_action action;
	int ret;

	action.mbox_cmd = (struct isst_if_mbox_cmd *)cmd_ptr;

	if (isst_if_mbox_cmd_invalid(action.mbox_cmd))
		return -EINVAL;

	if (isst_if_mbox_cmd_set_req(action.mbox_cmd) &&
	    !capable(CAP_SYS_ADMIN))
		return -EPERM;

	/*
	 * To complete mailbox command, we need to access two MSRs.
	 * So we don't want race to complete a mailbox transcation.
	 * Here smp_call ensures that msrl_update_func() has no race
	 * and also with wait flag, wait for completion.
	 * smp_call_function_single is using get_cpu() and put_cpu().
	 */
	ret = smp_call_function_single(action.mbox_cmd->logical_cpu,
				       msrl_update_func, &action, 1);
	if (ret)
		return ret;

	if (!action.err && !resume && isst_if_mbox_cmd_set_req(action.mbox_cmd))
		action.err = isst_store_cmd(action.mbox_cmd->command,
					    action.mbox_cmd->sub_command,
					    action.mbox_cmd->logical_cpu, 1,
					    action.mbox_cmd->parameter,
					    action.mbox_cmd->req_data);
	*write_only = 0;

	return action.err;
}