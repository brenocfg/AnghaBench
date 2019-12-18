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
struct host_cmd_ds_11n_delba {int dummy; } ;
struct TYPE_2__ {struct host_cmd_ds_11n_delba del_ba; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_11N_DELBA ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct host_cmd_ds_11n_delba*,void*,int) ; 

int mwifiex_cmd_11n_delba(struct host_cmd_ds_command *cmd, void *data_buf)
{
	struct host_cmd_ds_11n_delba *del_ba = &cmd->params.del_ba;

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_DELBA);
	cmd->size = cpu_to_le16(sizeof(*del_ba) + S_DS_GEN);
	memcpy(del_ba, data_buf, sizeof(*del_ba));

	return 0;
}