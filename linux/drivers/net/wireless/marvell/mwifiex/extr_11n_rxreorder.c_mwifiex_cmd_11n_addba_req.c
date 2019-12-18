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
struct host_cmd_ds_11n_addba_req {int dummy; } ;
struct TYPE_2__ {struct host_cmd_ds_11n_addba_req add_ba_req; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_11N_ADDBA_REQ ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct host_cmd_ds_11n_addba_req*,void*,int) ; 

int mwifiex_cmd_11n_addba_req(struct host_cmd_ds_command *cmd, void *data_buf)
{
	struct host_cmd_ds_11n_addba_req *add_ba_req = &cmd->params.add_ba_req;

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_ADDBA_REQ);
	cmd->size = cpu_to_le16(sizeof(*add_ba_req) + S_DS_GEN);
	memcpy(add_ba_req, data_buf, sizeof(*add_ba_req));

	return 0;
}