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
typedef  int /*<<< orphan*/  u16 ;
struct peak_usb_device {int /*<<< orphan*/  ctrl_idx; } ;
struct pcan_ufd_options {void* usb_mask; void* ucan_mask; int /*<<< orphan*/  opcode_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUCAN_CMD_CLR_DIS_OPTION ; 
 int /*<<< orphan*/  PUCAN_CMD_SET_EN_OPTION ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct pcan_ufd_options* pcan_usb_fd_cmd_buffer (struct peak_usb_device*) ; 
 int pcan_usb_fd_send_cmd (struct peak_usb_device*,struct pcan_ufd_options*) ; 
 int /*<<< orphan*/  pucan_cmd_opcode_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_fd_set_options(struct peak_usb_device *dev,
				   bool onoff, u16 ucan_mask, u16 usb_mask)
{
	struct pcan_ufd_options *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
					(onoff) ? PUCAN_CMD_SET_EN_OPTION :
						  PUCAN_CMD_CLR_DIS_OPTION);

	cmd->ucan_mask = cpu_to_le16(ucan_mask);
	cmd->usb_mask = cpu_to_le16(usb_mask);

	/* send the command */
	return pcan_usb_fd_send_cmd(dev, ++cmd);
}