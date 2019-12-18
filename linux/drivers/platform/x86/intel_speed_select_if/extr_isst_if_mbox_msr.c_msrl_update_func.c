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
struct msrl_action {TYPE_1__* mbox_cmd; int /*<<< orphan*/  err; } ;
struct TYPE_2__ {int /*<<< orphan*/  resp_data; int /*<<< orphan*/  req_data; int /*<<< orphan*/  parameter; int /*<<< orphan*/  sub_command; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  isst_if_send_mbox_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msrl_update_func(void *info)
{
	struct msrl_action *act = info;

	act->err = isst_if_send_mbox_cmd(act->mbox_cmd->command,
					 act->mbox_cmd->sub_command,
					 act->mbox_cmd->parameter,
					 act->mbox_cmd->req_data,
					 &act->mbox_cmd->resp_data);
}