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
typedef  scalar_t__ u8 ;
struct pucan_command {int /*<<< orphan*/  opcode_channel; } ;
struct peak_usb_device {int /*<<< orphan*/  ctrl_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUCAN_CMD_RESET_MODE ; 
 int pcan_usb_fd_build_restart_cmd (struct peak_usb_device*,scalar_t__*) ; 
 scalar_t__* pcan_usb_fd_cmd_buffer (struct peak_usb_device*) ; 
 int pcan_usb_fd_send_cmd (struct peak_usb_device*,scalar_t__*) ; 
 int /*<<< orphan*/  pucan_cmd_opcode_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_fd_set_bus(struct peak_usb_device *dev, u8 onoff)
{
	u8 *pc = pcan_usb_fd_cmd_buffer(dev);
	int l;

	if (onoff) {
		/* build the cmds list to enter operational mode */
		l = pcan_usb_fd_build_restart_cmd(dev, pc);
	} else {
		struct pucan_command *cmd = (struct pucan_command *)pc;

		/* build cmd to go back to reset mode */
		cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
							PUCAN_CMD_RESET_MODE);
		l = sizeof(struct pucan_command);
	}

	/* send the command */
	return pcan_usb_fd_send_cmd(dev, pc + l);
}