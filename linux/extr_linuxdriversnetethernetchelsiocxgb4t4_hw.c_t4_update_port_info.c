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
struct port_info {TYPE_2__* adapter; int /*<<< orphan*/  tx_chan; } ;
struct fw_port_cmd {void* action_to_len16; void* op_to_portid; } ;
typedef  int /*<<< orphan*/  port_cmd ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_3__ {unsigned int fw_caps_support; } ;
struct TYPE_4__ {int /*<<< orphan*/  mbox; TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int FW_CAPS16 ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_port_cmd) ; 
 int /*<<< orphan*/  FW_PORT_ACTION_GET_PORT_INFO ; 
 int /*<<< orphan*/  FW_PORT_ACTION_GET_PORT_INFO32 ; 
 int /*<<< orphan*/  FW_PORT_CMD ; 
 int FW_PORT_CMD_ACTION_V (int /*<<< orphan*/ ) ; 
 int FW_PORT_CMD_PORTID_V (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_port_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_handle_get_port_info (struct port_info*,int /*<<< orphan*/ *) ; 
 int t4_wr_mbox (TYPE_2__*,int /*<<< orphan*/ ,struct fw_port_cmd*,int,struct fw_port_cmd*) ; 

int t4_update_port_info(struct port_info *pi)
{
	unsigned int fw_caps = pi->adapter->params.fw_caps_support;
	struct fw_port_cmd port_cmd;
	int ret;

	memset(&port_cmd, 0, sizeof(port_cmd));
	port_cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
					    FW_CMD_REQUEST_F | FW_CMD_READ_F |
					    FW_PORT_CMD_PORTID_V(pi->tx_chan));
	port_cmd.action_to_len16 = cpu_to_be32(
		FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
				     ? FW_PORT_ACTION_GET_PORT_INFO
				     : FW_PORT_ACTION_GET_PORT_INFO32) |
		FW_LEN16(port_cmd));
	ret = t4_wr_mbox(pi->adapter, pi->adapter->mbox,
			 &port_cmd, sizeof(port_cmd), &port_cmd);
	if (ret)
		return ret;

	t4_handle_get_port_info(pi, (__be64 *)&port_cmd);
	return 0;
}