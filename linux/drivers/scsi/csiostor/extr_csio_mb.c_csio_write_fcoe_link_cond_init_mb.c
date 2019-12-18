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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_fcoe_link_cmd {int lstatus; void* retval_len16; void* sub_opcode_fcfi; void* op_to_portid; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_lnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_fcoe_link_cmd*,int /*<<< orphan*/ ,struct csio_lnode*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_FCOE_LINK_CMD ; 
 int FW_FCOE_LINK_CMD_FCFI (int /*<<< orphan*/ ) ; 
 int FW_FCOE_LINK_CMD_PORTID (int /*<<< orphan*/ ) ; 
 int FW_FCOE_LINK_CMD_SUB_OPCODE (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 

void
csio_write_fcoe_link_cond_init_mb(struct csio_lnode *ln, struct csio_mb *mbp,
			uint32_t mb_tmo, uint8_t port_id, uint32_t sub_opcode,
			uint8_t cos, bool link_status, uint32_t fcfi,
			void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_fcoe_link_cmd *cmdp =
				(struct fw_fcoe_link_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_tmo, ln, cbfn, 1);

	cmdp->op_to_portid = htonl((
			FW_CMD_OP_V(FW_FCOE_LINK_CMD)		|
			FW_CMD_REQUEST_F				|
			FW_CMD_WRITE_F				|
			FW_FCOE_LINK_CMD_PORTID(port_id)));
	cmdp->sub_opcode_fcfi = htonl(
			FW_FCOE_LINK_CMD_SUB_OPCODE(sub_opcode)	|
			FW_FCOE_LINK_CMD_FCFI(fcfi));
	cmdp->lstatus = link_status;
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(sizeof(*cmdp) / 16));

}