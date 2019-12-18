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
struct pucan_timing_fast {int /*<<< orphan*/  brp; int /*<<< orphan*/  tseg1; int /*<<< orphan*/  tseg2; int /*<<< orphan*/  sjw; int /*<<< orphan*/  opcode_channel; } ;
struct peak_usb_device {int /*<<< orphan*/  ctrl_idx; } ;
struct can_bittiming {scalar_t__ brp; scalar_t__ phase_seg1; scalar_t__ prop_seg; scalar_t__ phase_seg2; scalar_t__ sjw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUCAN_CMD_TIMING_FAST ; 
 int /*<<< orphan*/  PUCAN_TFAST_BRP (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TFAST_SJW (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TFAST_TSEG1 (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TFAST_TSEG2 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct pucan_timing_fast* pcan_usb_fd_cmd_buffer (struct peak_usb_device*) ; 
 int pcan_usb_fd_send_cmd (struct peak_usb_device*,struct pucan_timing_fast*) ; 
 int /*<<< orphan*/  pucan_cmd_opcode_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_fd_set_bittiming_fast(struct peak_usb_device *dev,
					  struct can_bittiming *bt)
{
	struct pucan_timing_fast *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PUCAN_CMD_TIMING_FAST);
	cmd->sjw = PUCAN_TFAST_SJW(bt->sjw - 1);
	cmd->tseg2 = PUCAN_TFAST_TSEG2(bt->phase_seg2 - 1);
	cmd->tseg1 = PUCAN_TFAST_TSEG1(bt->prop_seg + bt->phase_seg1 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TFAST_BRP(bt->brp - 1));

	/* send the command */
	return pcan_usb_fd_send_cmd(dev, ++cmd);
}