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
struct ena_comp_ctx {int dummy; } ;
struct ena_com_admin_queue {scalar_t__ running_state; } ;
struct ena_admin_aq_entry {int dummy; } ;
struct ena_admin_acq_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct ena_comp_ctx* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ena_comp_ctx*) ; 
 int PTR_ERR (struct ena_comp_ctx*) ; 
 struct ena_comp_ctx* ena_com_submit_admin_cmd (struct ena_com_admin_queue*,struct ena_admin_aq_entry*,size_t,struct ena_admin_acq_entry*,size_t) ; 
 int ena_com_wait_and_process_admin_cq (struct ena_comp_ctx*,struct ena_com_admin_queue*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_execute_admin_command(struct ena_com_admin_queue *admin_queue,
				  struct ena_admin_aq_entry *cmd,
				  size_t cmd_size,
				  struct ena_admin_acq_entry *comp,
				  size_t comp_size)
{
	struct ena_comp_ctx *comp_ctx;
	int ret;

	comp_ctx = ena_com_submit_admin_cmd(admin_queue, cmd, cmd_size,
					    comp, comp_size);
	if (IS_ERR(comp_ctx)) {
		if (comp_ctx == ERR_PTR(-ENODEV))
			pr_debug("Failed to submit command [%ld]\n",
				 PTR_ERR(comp_ctx));
		else
			pr_err("Failed to submit command [%ld]\n",
			       PTR_ERR(comp_ctx));

		return PTR_ERR(comp_ctx);
	}

	ret = ena_com_wait_and_process_admin_cq(comp_ctx, admin_queue);
	if (unlikely(ret)) {
		if (admin_queue->running_state)
			pr_err("Failed to process command. ret = %d\n", ret);
		else
			pr_debug("Failed to process command. ret = %d\n", ret);
	}
	return ret;
}