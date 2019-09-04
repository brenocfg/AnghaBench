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
struct TYPE_4__ {void* rcap; } ;
struct TYPE_3__ {TYPE_2__ l1cfg; } ;
struct fw_port_cmd {TYPE_1__ u; void* action_to_len16; void* op_to_portid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_CMD_EXEC_F ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_port_cmd) ; 
 int /*<<< orphan*/  FW_PORT_ACTION_L1_CFG ; 
 int FW_PORT_CAP32_ANEG ; 
 int /*<<< orphan*/  FW_PORT_CMD ; 
 int FW_PORT_CMD_ACTION_V (int /*<<< orphan*/ ) ; 
 int FW_PORT_CMD_PORTID_V (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_port_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_port_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_restart_aneg(struct adapter *adap, unsigned int mbox, unsigned int port)
{
	struct fw_port_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
				     FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				     FW_PORT_CMD_PORTID_V(port));
	c.action_to_len16 =
		cpu_to_be32(FW_PORT_CMD_ACTION_V(FW_PORT_ACTION_L1_CFG) |
			    FW_LEN16(c));
	c.u.l1cfg.rcap = cpu_to_be32(FW_PORT_CAP32_ANEG);
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}