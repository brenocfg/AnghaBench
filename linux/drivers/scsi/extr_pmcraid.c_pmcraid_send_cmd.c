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
struct TYPE_2__ {void (* function ) (struct timer_list*) ;scalar_t__ expires; } ;
struct pmcraid_cmd {void (* cmd_done ) (struct pmcraid_cmd*) ;TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _pmcraid_fire_command (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void pmcraid_send_cmd(
	struct pmcraid_cmd *cmd,
	void (*cmd_done) (struct pmcraid_cmd *),
	unsigned long timeout,
	void (*timeout_func) (struct timer_list *)
)
{
	/* initialize done function */
	cmd->cmd_done = cmd_done;

	if (timeout_func) {
		/* setup timeout handler */
		cmd->timer.expires = jiffies + timeout;
		cmd->timer.function = timeout_func;
		add_timer(&cmd->timer);
	}

	/* fire the command to IOA */
	_pmcraid_fire_command(cmd);
}