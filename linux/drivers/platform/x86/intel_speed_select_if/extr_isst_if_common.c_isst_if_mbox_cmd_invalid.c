#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct isst_if_mbox_cmd {scalar_t__ logical_cpu; scalar_t__ command; scalar_t__ sub_command; } ;
struct TYPE_3__ {scalar_t__ cmd; scalar_t__ sub_cmd_beg; scalar_t__ sub_cmd_end; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* isst_valid_cmds ; 
 scalar_t__ nr_cpu_ids ; 

bool isst_if_mbox_cmd_invalid(struct isst_if_mbox_cmd *cmd)
{
	int i;

	if (cmd->logical_cpu >= nr_cpu_ids)
		return true;

	for (i = 0; i < ARRAY_SIZE(isst_valid_cmds); ++i) {
		if (cmd->command == isst_valid_cmds[i].cmd &&
		    (cmd->sub_command >= isst_valid_cmds[i].sub_cmd_beg &&
		     cmd->sub_command <= isst_valid_cmds[i].sub_cmd_end)) {
			return false;
		}
	}

	return true;
}