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
typedef  int u32 ;
struct its_node {scalar_t__ cmd_write; scalar_t__ cmd_base; } ;
struct its_cmd_block {scalar_t__* raw_cmd; } ;

/* Variables and functions */
 scalar_t__ ITS_CMD_QUEUE_NR_ENTRIES ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ its_queue_full (struct its_node*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static struct its_cmd_block *its_allocate_entry(struct its_node *its)
{
	struct its_cmd_block *cmd;
	u32 count = 1000000;	/* 1s! */

	while (its_queue_full(its)) {
		count--;
		if (!count) {
			pr_err_ratelimited("ITS queue not draining\n");
			return NULL;
		}
		cpu_relax();
		udelay(1);
	}

	cmd = its->cmd_write++;

	/* Handle queue wrapping */
	if (its->cmd_write == (its->cmd_base + ITS_CMD_QUEUE_NR_ENTRIES))
		its->cmd_write = its->cmd_base;

	/* Clear command  */
	cmd->raw_cmd[0] = 0;
	cmd->raw_cmd[1] = 0;
	cmd->raw_cmd[2] = 0;
	cmd->raw_cmd[3] = 0;

	return cmd;
}