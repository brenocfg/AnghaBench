#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct port_info {TYPE_5__* adapter; int /*<<< orphan*/  tx_chan; } ;
struct TYPE_8__ {int /*<<< orphan*/  auxlinfo32_mtu32; int /*<<< orphan*/  linkattr32; int /*<<< orphan*/  lstatus32_to_cbllen32; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  lstatus_to_modtype; } ;
struct TYPE_9__ {TYPE_3__ info32; TYPE_2__ info; } ;
struct fw_port_cmd {TYPE_4__ u; void* action_to_len16; void* op_to_portid; } ;
typedef  int /*<<< orphan*/  port_cmd ;
typedef  void* fw_port_cap32_t ;
struct TYPE_6__ {unsigned int fw_caps_support; } ;
struct TYPE_10__ {int /*<<< orphan*/  mbox; TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int FW_CAPS16 ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_port_cmd) ; 
 unsigned int FW_PORT_ACTION_GET_PORT_INFO ; 
 unsigned int FW_PORT_ACTION_GET_PORT_INFO32 ; 
 int /*<<< orphan*/  FW_PORT_CMD ; 
 int FW_PORT_CMD_ACTION_V (unsigned int) ; 
 int FW_PORT_CMD_LSTATUS32_F ; 
 int FW_PORT_CMD_LSTATUS_F ; 
 unsigned int FW_PORT_CMD_MTU32_G (void*) ; 
 int FW_PORT_CMD_PORTID_V (int /*<<< orphan*/ ) ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 unsigned int fwcap_to_speed (void*) ; 
 void* lstatus_to_fwcap (int) ; 
 int /*<<< orphan*/  memset (struct fw_port_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (TYPE_5__*,int /*<<< orphan*/ ,struct fw_port_cmd*,int,struct fw_port_cmd*) ; 

int t4_get_link_params(struct port_info *pi, unsigned int *link_okp,
		       unsigned int *speedp, unsigned int *mtup)
{
	unsigned int fw_caps = pi->adapter->params.fw_caps_support;
	struct fw_port_cmd port_cmd;
	unsigned int action, link_ok, mtu;
	fw_port_cap32_t linkattr;
	int ret;

	memset(&port_cmd, 0, sizeof(port_cmd));
	port_cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
					    FW_CMD_REQUEST_F | FW_CMD_READ_F |
					    FW_PORT_CMD_PORTID_V(pi->tx_chan));
	action = (fw_caps == FW_CAPS16
		  ? FW_PORT_ACTION_GET_PORT_INFO
		  : FW_PORT_ACTION_GET_PORT_INFO32);
	port_cmd.action_to_len16 = cpu_to_be32(
		FW_PORT_CMD_ACTION_V(action) |
		FW_LEN16(port_cmd));
	ret = t4_wr_mbox(pi->adapter, pi->adapter->mbox,
			 &port_cmd, sizeof(port_cmd), &port_cmd);
	if (ret)
		return ret;

	if (action == FW_PORT_ACTION_GET_PORT_INFO) {
		u32 lstatus = be32_to_cpu(port_cmd.u.info.lstatus_to_modtype);

		link_ok = !!(lstatus & FW_PORT_CMD_LSTATUS_F);
		linkattr = lstatus_to_fwcap(lstatus);
		mtu = be16_to_cpu(port_cmd.u.info.mtu);
	} else {
		u32 lstatus32 =
			   be32_to_cpu(port_cmd.u.info32.lstatus32_to_cbllen32);

		link_ok = !!(lstatus32 & FW_PORT_CMD_LSTATUS32_F);
		linkattr = be32_to_cpu(port_cmd.u.info32.linkattr32);
		mtu = FW_PORT_CMD_MTU32_G(
			be32_to_cpu(port_cmd.u.info32.auxlinfo32_mtu32));
	}

	*link_okp = link_ok;
	*speedp = fwcap_to_speed(linkattr);
	*mtup = mtu;

	return 0;
}