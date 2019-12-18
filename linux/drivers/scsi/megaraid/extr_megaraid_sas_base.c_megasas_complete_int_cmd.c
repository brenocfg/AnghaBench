#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct megasas_instance {int /*<<< orphan*/  int_cmd_wait_q; } ;
struct megasas_cmd {TYPE_2__* frame; int /*<<< orphan*/  cmd_status_drv; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_status; } ;
struct TYPE_4__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
megasas_complete_int_cmd(struct megasas_instance *instance,
			 struct megasas_cmd *cmd)
{
	cmd->cmd_status_drv = cmd->frame->io.cmd_status;
	wake_up(&instance->int_cmd_wait_q);
}