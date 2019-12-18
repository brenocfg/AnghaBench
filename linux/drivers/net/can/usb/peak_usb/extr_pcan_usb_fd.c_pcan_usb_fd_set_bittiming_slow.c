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
struct pucan_timing_slow {int ewl; int /*<<< orphan*/  brp; int /*<<< orphan*/  tseg1; int /*<<< orphan*/  tseg2; int /*<<< orphan*/  sjw_t; int /*<<< orphan*/  opcode_channel; } ;
struct TYPE_2__ {int ctrlmode; } ;
struct peak_usb_device {TYPE_1__ can; int /*<<< orphan*/  ctrl_idx; } ;
struct can_bittiming {scalar_t__ brp; scalar_t__ phase_seg1; scalar_t__ prop_seg; scalar_t__ phase_seg2; scalar_t__ sjw; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  PUCAN_CMD_TIMING_SLOW ; 
 int /*<<< orphan*/  PUCAN_TSLOW_BRP (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TSLOW_SJW_T (scalar_t__,int) ; 
 int /*<<< orphan*/  PUCAN_TSLOW_TSEG1 (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TSLOW_TSEG2 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct pucan_timing_slow* pcan_usb_fd_cmd_buffer (struct peak_usb_device*) ; 
 int pcan_usb_fd_send_cmd (struct peak_usb_device*,struct pucan_timing_slow*) ; 
 int /*<<< orphan*/  pucan_cmd_opcode_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_fd_set_bittiming_slow(struct peak_usb_device *dev,
					  struct can_bittiming *bt)
{
	struct pucan_timing_slow *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PUCAN_CMD_TIMING_SLOW);
	cmd->sjw_t = PUCAN_TSLOW_SJW_T(bt->sjw - 1,
				dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES);

	cmd->tseg2 = PUCAN_TSLOW_TSEG2(bt->phase_seg2 - 1);
	cmd->tseg1 = PUCAN_TSLOW_TSEG1(bt->prop_seg + bt->phase_seg1 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TSLOW_BRP(bt->brp - 1));

	cmd->ewl = 96;	/* default */

	/* send the command */
	return pcan_usb_fd_send_cmd(dev, ++cmd);
}