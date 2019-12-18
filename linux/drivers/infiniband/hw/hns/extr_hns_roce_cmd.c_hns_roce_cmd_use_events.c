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
struct hns_roce_cmdq {int max_cmds; int use_events; int /*<<< orphan*/  token_mask; int /*<<< orphan*/  context_lock; int /*<<< orphan*/  event_sem; scalar_t__ free_head; TYPE_1__* context; } ;
struct hns_roce_dev {struct hns_roce_cmdq cmd; } ;
struct TYPE_2__ {int token; int next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TOKEN_MASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hns_roce_cmd_use_events(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_cmdq *hr_cmd = &hr_dev->cmd;
	int i;

	hr_cmd->context = kmalloc_array(hr_cmd->max_cmds,
					sizeof(*hr_cmd->context),
					GFP_KERNEL);
	if (!hr_cmd->context)
		return -ENOMEM;

	for (i = 0; i < hr_cmd->max_cmds; ++i) {
		hr_cmd->context[i].token = i;
		hr_cmd->context[i].next = i + 1;
	}

	hr_cmd->context[hr_cmd->max_cmds - 1].next = -1;
	hr_cmd->free_head = 0;

	sema_init(&hr_cmd->event_sem, hr_cmd->max_cmds);
	spin_lock_init(&hr_cmd->context_lock);

	hr_cmd->token_mask = CMD_TOKEN_MASK;
	hr_cmd->use_events = 1;

	return 0;
}