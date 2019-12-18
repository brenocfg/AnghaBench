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
struct TYPE_4__ {int /*<<< orphan*/  family; } ;
struct TYPE_5__ {TYPE_1__ leaf; } ;
struct kvaser_usb {TYPE_3__* intf; TYPE_2__ card_data; } ;
struct kvaser_cmd {int id; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_CAN_ERROR_EVENT 137 
#define  CMD_CHIP_STATE_EVENT 136 
#define  CMD_FLUSH_QUEUE_REPLY 135 
#define  CMD_LEAF_LOG_MESSAGE 134 
#define  CMD_RX_EXT_MESSAGE 133 
#define  CMD_RX_STD_MESSAGE 132 
#define  CMD_START_CHIP_REPLY 131 
#define  CMD_STOP_CHIP_REPLY 130 
#define  CMD_TX_ACKNOWLEDGE 129 
#define  CMD_USBCAN_CLOCK_OVERFLOW_EVENT 128 
 int /*<<< orphan*/  KVASER_LEAF ; 
 int /*<<< orphan*/  KVASER_USBCAN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_leaf_rx_error (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_rx_can_msg (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_start_chip_reply (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_stop_chip_reply (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_tx_acknowledge (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_usbcan_rx_error (struct kvaser_usb const*,struct kvaser_cmd const*) ; 

__attribute__((used)) static void kvaser_usb_leaf_handle_command(const struct kvaser_usb *dev,
					   const struct kvaser_cmd *cmd)
{
	switch (cmd->id) {
	case CMD_START_CHIP_REPLY:
		kvaser_usb_leaf_start_chip_reply(dev, cmd);
		break;

	case CMD_STOP_CHIP_REPLY:
		kvaser_usb_leaf_stop_chip_reply(dev, cmd);
		break;

	case CMD_RX_STD_MESSAGE:
	case CMD_RX_EXT_MESSAGE:
		kvaser_usb_leaf_rx_can_msg(dev, cmd);
		break;

	case CMD_LEAF_LOG_MESSAGE:
		if (dev->card_data.leaf.family != KVASER_LEAF)
			goto warn;
		kvaser_usb_leaf_rx_can_msg(dev, cmd);
		break;

	case CMD_CHIP_STATE_EVENT:
	case CMD_CAN_ERROR_EVENT:
		if (dev->card_data.leaf.family == KVASER_LEAF)
			kvaser_usb_leaf_leaf_rx_error(dev, cmd);
		else
			kvaser_usb_leaf_usbcan_rx_error(dev, cmd);
		break;

	case CMD_TX_ACKNOWLEDGE:
		kvaser_usb_leaf_tx_acknowledge(dev, cmd);
		break;

	/* Ignored commands */
	case CMD_USBCAN_CLOCK_OVERFLOW_EVENT:
		if (dev->card_data.leaf.family != KVASER_USBCAN)
			goto warn;
		break;

	case CMD_FLUSH_QUEUE_REPLY:
		if (dev->card_data.leaf.family != KVASER_LEAF)
			goto warn;
		break;

	default:
warn:		dev_warn(&dev->intf->dev, "Unhandled command (%d)\n", cmd->id);
		break;
	}
}