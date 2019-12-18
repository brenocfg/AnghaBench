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
typedef  int /*<<< orphan*/  u8 ;
struct peak_usb_device {int /*<<< orphan*/  ctrl_idx; } ;
struct pcan_ufd_led {int /*<<< orphan*/  mode; int /*<<< orphan*/  opcode_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAN_UFD_CMD_LED_SET ; 
 struct pcan_ufd_led* pcan_usb_fd_cmd_buffer (struct peak_usb_device*) ; 
 int pcan_usb_fd_send_cmd (struct peak_usb_device*,struct pcan_ufd_led*) ; 
 int /*<<< orphan*/  pucan_cmd_opcode_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_fd_set_can_led(struct peak_usb_device *dev, u8 led_mode)
{
	struct pcan_ufd_led *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PCAN_UFD_CMD_LED_SET);
	cmd->mode = led_mode;

	/* send the command */
	return pcan_usb_fd_send_cmd(dev, ++cmd);
}