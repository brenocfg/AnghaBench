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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct hns_roce_cmdq {size_t free_head; int /*<<< orphan*/  context_lock; struct hns_roce_cmd_context* context; scalar_t__ token_mask; } ;
struct hns_roce_dev {struct device* dev; struct hns_roce_cmdq cmd; } ;
struct hns_roce_cmd_context {size_t next; int result; int /*<<< orphan*/  done; int /*<<< orphan*/  token; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int hns_roce_cmd_mbox_post_hw (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __hns_roce_cmd_mbox_wait(struct hns_roce_dev *hr_dev, u64 in_param,
				    u64 out_param, unsigned long in_modifier,
				    u8 op_modifier, u16 op,
				    unsigned long timeout)
{
	struct hns_roce_cmdq *cmd = &hr_dev->cmd;
	struct hns_roce_cmd_context *context;
	struct device *dev = hr_dev->dev;
	int ret;

	spin_lock(&cmd->context_lock);
	WARN_ON(cmd->free_head < 0);
	context = &cmd->context[cmd->free_head];
	context->token += cmd->token_mask + 1;
	cmd->free_head = context->next;
	spin_unlock(&cmd->context_lock);

	init_completion(&context->done);

	ret = hns_roce_cmd_mbox_post_hw(hr_dev, in_param, out_param,
					in_modifier, op_modifier, op,
					context->token, 1);
	if (ret)
		goto out;

	/*
	 * It is timeout when wait_for_completion_timeout return 0
	 * The return value is the time limit set in advance
	 * how many seconds showing
	 */
	if (!wait_for_completion_timeout(&context->done,
					 msecs_to_jiffies(timeout))) {
		dev_err(dev, "[cmd]wait_for_completion_timeout timeout\n");
		ret = -EBUSY;
		goto out;
	}

	ret = context->result;
	if (ret) {
		dev_err(dev, "[cmd]event mod cmd process error!err=%d\n", ret);
		goto out;
	}

out:
	spin_lock(&cmd->context_lock);
	context->next = cmd->free_head;
	cmd->free_head = context - cmd->context;
	spin_unlock(&cmd->context_lock);

	return ret;
}