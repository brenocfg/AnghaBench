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
struct efa_comp_ctx {int /*<<< orphan*/  comp_status; } ;
struct efa_com_admin_queue {int /*<<< orphan*/  avail_cmds; int /*<<< orphan*/  efa_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct efa_admin_aq_entry {TYPE_1__ aq_common_descriptor; } ;
struct efa_admin_acq_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct efa_comp_ctx*) ; 
 int PTR_ERR (struct efa_comp_ctx*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efa_com_cmd_str (int /*<<< orphan*/ ) ; 
 struct efa_comp_ctx* efa_com_submit_admin_cmd (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,size_t,struct efa_admin_acq_entry*,size_t) ; 
 int efa_com_wait_and_process_admin_cq (struct efa_comp_ctx*,struct efa_com_admin_queue*) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int efa_com_cmd_exec(struct efa_com_admin_queue *aq,
		     struct efa_admin_aq_entry *cmd,
		     size_t cmd_size,
		     struct efa_admin_acq_entry *comp,
		     size_t comp_size)
{
	struct efa_comp_ctx *comp_ctx;
	int err;

	might_sleep();

	/* In case of queue FULL */
	down(&aq->avail_cmds);

	ibdev_dbg(aq->efa_dev, "%s (opcode %d)\n",
		  efa_com_cmd_str(cmd->aq_common_descriptor.opcode),
		  cmd->aq_common_descriptor.opcode);
	comp_ctx = efa_com_submit_admin_cmd(aq, cmd, cmd_size, comp, comp_size);
	if (IS_ERR(comp_ctx)) {
		ibdev_err_ratelimited(
			aq->efa_dev,
			"Failed to submit command %s (opcode %u) err %ld\n",
			efa_com_cmd_str(cmd->aq_common_descriptor.opcode),
			cmd->aq_common_descriptor.opcode, PTR_ERR(comp_ctx));

		up(&aq->avail_cmds);
		return PTR_ERR(comp_ctx);
	}

	err = efa_com_wait_and_process_admin_cq(comp_ctx, aq);
	if (err)
		ibdev_err_ratelimited(
			aq->efa_dev,
			"Failed to process command %s (opcode %u) comp_status %d err %d\n",
			efa_com_cmd_str(cmd->aq_common_descriptor.opcode),
			cmd->aq_common_descriptor.opcode, comp_ctx->comp_status,
			err);

	up(&aq->avail_cmds);

	return err;
}