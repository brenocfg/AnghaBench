#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvaser_usb {TYPE_1__* intf; } ;
struct TYPE_4__ {int cmd_no; } ;
struct kvaser_cmd {TYPE_2__ header; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_CHIP_STATE_EVENT 136 
#define  CMD_ERROR_EVENT 135 
#define  CMD_FLUSH_QUEUE_RESP 134 
#define  CMD_RX_MESSAGE 133 
#define  CMD_SET_BUSPARAMS_FD_RESP 132 
#define  CMD_SET_BUSPARAMS_RESP 131 
#define  CMD_START_CHIP_RESP 130 
#define  CMD_STOP_CHIP_RESP 129 
#define  CMD_TX_ACKNOWLEDGE 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_error_event (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_flush_queue_reply (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_rx_msg_std (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_start_chip_reply (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_state_event (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_stop_chip_reply (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_tx_acknowledge (struct kvaser_usb const*,struct kvaser_cmd const*) ; 

__attribute__((used)) static void kvaser_usb_hydra_handle_cmd_std(const struct kvaser_usb *dev,
					    const struct kvaser_cmd *cmd)
{
	switch (cmd->header.cmd_no) {
	case CMD_START_CHIP_RESP:
		kvaser_usb_hydra_start_chip_reply(dev, cmd);
		break;

	case CMD_STOP_CHIP_RESP:
		kvaser_usb_hydra_stop_chip_reply(dev, cmd);
		break;

	case CMD_FLUSH_QUEUE_RESP:
		kvaser_usb_hydra_flush_queue_reply(dev, cmd);
		break;

	case CMD_CHIP_STATE_EVENT:
		kvaser_usb_hydra_state_event(dev, cmd);
		break;

	case CMD_ERROR_EVENT:
		kvaser_usb_hydra_error_event(dev, cmd);
		break;

	case CMD_TX_ACKNOWLEDGE:
		kvaser_usb_hydra_tx_acknowledge(dev, cmd);
		break;

	case CMD_RX_MESSAGE:
		kvaser_usb_hydra_rx_msg_std(dev, cmd);
		break;

	/* Ignored commands */
	case CMD_SET_BUSPARAMS_RESP:
	case CMD_SET_BUSPARAMS_FD_RESP:
		break;

	default:
		dev_warn(&dev->intf->dev, "Unhandled command (%d)\n",
			 cmd->header.cmd_no);
		break;
	}
}