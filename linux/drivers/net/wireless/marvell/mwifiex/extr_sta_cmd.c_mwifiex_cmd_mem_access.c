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
typedef  scalar_t__ u16 ;
struct mwifiex_ds_mem_rw {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
struct host_cmd_ds_mem_access {void* value; void* addr; void* action; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_MEM_ACCESS ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_cmd_mem_access(struct host_cmd_ds_command *cmd, u16 cmd_action,
		       void *pdata_buf)
{
	struct mwifiex_ds_mem_rw *mem_rw = (void *)pdata_buf;
	struct host_cmd_ds_mem_access *mem_access = (void *)&cmd->params.mem;

	cmd->command = cpu_to_le16(HostCmd_CMD_MEM_ACCESS);
	cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_mem_access) +
				S_DS_GEN);

	mem_access->action = cpu_to_le16(cmd_action);
	mem_access->addr = cpu_to_le32(mem_rw->addr);
	mem_access->value = cpu_to_le32(mem_rw->value);

	return 0;
}