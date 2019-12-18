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
typedef  int /*<<< orphan*/  u8 ;
struct pucan_wr_err_cnt {scalar_t__ rx_counter; scalar_t__ tx_counter; void* sel_mask; void* opcode_channel; } ;
struct pucan_options {scalar_t__ unused; void* options; void* opcode_channel; } ;
struct pucan_command {void* opcode_channel; } ;
struct TYPE_2__ {int ctrlmode_supported; int ctrlmode; } ;
struct peak_usb_device {TYPE_1__ can; int /*<<< orphan*/  ctrl_idx; } ;

/* Variables and functions */
 int CAN_CTRLMODE_FD_NON_ISO ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int /*<<< orphan*/  PUCAN_CMD_CLR_DIS_OPTION ; 
 int /*<<< orphan*/  PUCAN_CMD_LISTEN_ONLY_MODE ; 
 int /*<<< orphan*/  PUCAN_CMD_NORMAL_MODE ; 
 int /*<<< orphan*/  PUCAN_CMD_SET_EN_OPTION ; 
 int /*<<< orphan*/  PUCAN_CMD_WR_ERR_CNT ; 
 int PUCAN_OPTION_CANDFDISO ; 
 int PUCAN_WRERRCNT_RE ; 
 int PUCAN_WRERRCNT_TE ; 
 void* cpu_to_le16 (int) ; 
 void* pucan_cmd_opcode_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_fd_build_restart_cmd(struct peak_usb_device *dev, u8 *buf)
{
	struct pucan_wr_err_cnt *prc;
	struct pucan_command *cmd;
	u8 *pc = buf;

	/* 1st, reset error counters: */
	prc = (struct pucan_wr_err_cnt *)pc;
	prc->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PUCAN_CMD_WR_ERR_CNT);

	/* select both counters */
	prc->sel_mask = cpu_to_le16(PUCAN_WRERRCNT_TE|PUCAN_WRERRCNT_RE);

	/* and reset their values */
	prc->tx_counter = 0;
	prc->rx_counter = 0;

	/* moves the pointer forward */
	pc += sizeof(struct pucan_wr_err_cnt);

	/* add command to switch from ISO to non-ISO mode, if fw allows it */
	if (dev->can.ctrlmode_supported & CAN_CTRLMODE_FD_NON_ISO) {
		struct pucan_options *puo = (struct pucan_options *)pc;

		puo->opcode_channel =
			(dev->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO) ?
			pucan_cmd_opcode_channel(dev->ctrl_idx,
						 PUCAN_CMD_CLR_DIS_OPTION) :
			pucan_cmd_opcode_channel(dev->ctrl_idx,
						 PUCAN_CMD_SET_EN_OPTION);

		puo->options = cpu_to_le16(PUCAN_OPTION_CANDFDISO);

		/* to be sure that no other extended bits will be taken into
		 * account
		 */
		puo->unused = 0;

		/* moves the pointer forward */
		pc += sizeof(struct pucan_options);
	}

	/* next, go back to operational mode */
	cmd = (struct pucan_command *)pc;
	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
				(dev->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) ?
						PUCAN_CMD_LISTEN_ONLY_MODE :
						PUCAN_CMD_NORMAL_MODE);
	pc += sizeof(struct pucan_command);

	return pc - buf;
}