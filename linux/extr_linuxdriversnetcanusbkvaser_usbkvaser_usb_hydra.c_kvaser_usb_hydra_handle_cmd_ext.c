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
struct TYPE_4__ {int /*<<< orphan*/  cmd_no; } ;
struct kvaser_cmd_ext {int cmd_no_ext; TYPE_2__ header; } ;
struct kvaser_cmd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_RX_MESSAGE_FD 129 
#define  CMD_TX_ACKNOWLEDGE_FD 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_rx_msg_ext (struct kvaser_usb const*,struct kvaser_cmd_ext const*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_tx_acknowledge (struct kvaser_usb const*,struct kvaser_cmd*) ; 

__attribute__((used)) static void kvaser_usb_hydra_handle_cmd_ext(const struct kvaser_usb *dev,
					    const struct kvaser_cmd_ext *cmd)
{
	switch (cmd->cmd_no_ext) {
	case CMD_TX_ACKNOWLEDGE_FD:
		kvaser_usb_hydra_tx_acknowledge(dev, (struct kvaser_cmd *)cmd);
		break;

	case CMD_RX_MESSAGE_FD:
		kvaser_usb_hydra_rx_msg_ext(dev, cmd);
		break;

	default:
		dev_warn(&dev->intf->dev, "Unhandled extended command (%d)\n",
			 cmd->header.cmd_no);
		break;
	}
}