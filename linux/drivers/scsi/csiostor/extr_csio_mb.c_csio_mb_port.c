#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {void* rcap32; } ;
struct TYPE_4__ {void* rcap; } ;
struct TYPE_6__ {TYPE_2__ l1cfg32; TYPE_1__ l1cfg; } ;
struct fw_port_cmd {TYPE_3__ u; void* action_to_len16; void* op_to_portid; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_port_cmd*,int /*<<< orphan*/ ,struct csio_hw*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 scalar_t__ FW_CAPS16 ; 
 int FW_CMD_EXEC_F ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_PORT_ACTION_GET_PORT_INFO ; 
 int /*<<< orphan*/  FW_PORT_ACTION_GET_PORT_INFO32 ; 
 int /*<<< orphan*/  FW_PORT_ACTION_L1_CFG ; 
 int /*<<< orphan*/  FW_PORT_ACTION_L1_CFG32 ; 
 int /*<<< orphan*/  FW_PORT_CMD ; 
 int FW_PORT_CMD_ACTION_V (int /*<<< orphan*/ ) ; 
 int FW_PORT_CMD_PORTID_V (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwcaps32_to_caps16 (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 

void
csio_mb_port(struct csio_hw *hw, struct csio_mb *mbp, uint32_t tmo,
	     u8 portid, bool wr, uint32_t fc, uint16_t fw_caps,
	     void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_port_cmd *cmdp = (struct fw_port_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, tmo, hw, cbfn,  1);

	cmdp->op_to_portid = htonl(FW_CMD_OP_V(FW_PORT_CMD)		|
				   FW_CMD_REQUEST_F			|
				   (wr ? FW_CMD_EXEC_F : FW_CMD_READ_F)	|
				   FW_PORT_CMD_PORTID_V(portid));
	if (!wr) {
		cmdp->action_to_len16 = htonl(
			FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
			? FW_PORT_ACTION_GET_PORT_INFO
			: FW_PORT_ACTION_GET_PORT_INFO32) |
			FW_CMD_LEN16_V(sizeof(*cmdp) / 16));
		return;
	}

	/* Set port */
	cmdp->action_to_len16 = htonl(
			FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
			? FW_PORT_ACTION_L1_CFG
			: FW_PORT_ACTION_L1_CFG32) |
			FW_CMD_LEN16_V(sizeof(*cmdp) / 16));

	if (fw_caps == FW_CAPS16)
		cmdp->u.l1cfg.rcap = cpu_to_be32(fwcaps32_to_caps16(fc));
	else
		cmdp->u.l1cfg32.rcap32 = cpu_to_be32(fc);
}