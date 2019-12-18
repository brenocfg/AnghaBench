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
struct its_cmd_block {void** raw_cmd; } ;

/* Variables and functions */
 void* cpu_to_le64 (void*) ; 

__attribute__((used)) static inline void its_fixup_cmd(struct its_cmd_block *cmd)
{
	/* Let's fixup BE commands */
	cmd->raw_cmd[0] = cpu_to_le64(cmd->raw_cmd[0]);
	cmd->raw_cmd[1] = cpu_to_le64(cmd->raw_cmd[1]);
	cmd->raw_cmd[2] = cpu_to_le64(cmd->raw_cmd[2]);
	cmd->raw_cmd[3] = cpu_to_le64(cmd->raw_cmd[3]);
}