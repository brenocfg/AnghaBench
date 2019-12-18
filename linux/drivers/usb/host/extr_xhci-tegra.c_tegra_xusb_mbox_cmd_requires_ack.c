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
typedef  enum tegra_xusb_mbox_cmd { ____Placeholder_tegra_xusb_mbox_cmd } tegra_xusb_mbox_cmd ;

/* Variables and functions */
#define  MBOX_CMD_ACK 130 
#define  MBOX_CMD_NAK 129 
#define  MBOX_CMD_SET_BW 128 

__attribute__((used)) static bool tegra_xusb_mbox_cmd_requires_ack(enum tegra_xusb_mbox_cmd cmd)
{
	switch (cmd) {
	case MBOX_CMD_SET_BW:
	case MBOX_CMD_ACK:
	case MBOX_CMD_NAK:
		return false;

	default:
		return true;
	}
}