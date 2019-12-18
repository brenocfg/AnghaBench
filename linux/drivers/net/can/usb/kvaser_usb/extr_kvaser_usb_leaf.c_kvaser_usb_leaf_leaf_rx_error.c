#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  error_factor; } ;
struct kvaser_usb_err_summary {TYPE_6__ leaf; int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; int /*<<< orphan*/  status; int /*<<< orphan*/  channel; } ;
struct kvaser_usb {TYPE_7__* intf; } ;
struct TYPE_10__ {int /*<<< orphan*/  rx_errors_count; int /*<<< orphan*/  tx_errors_count; int /*<<< orphan*/  status; int /*<<< orphan*/  channel; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  channel; } ;
struct TYPE_8__ {int /*<<< orphan*/  error_factor; int /*<<< orphan*/  rx_errors_count; int /*<<< orphan*/  tx_errors_count; int /*<<< orphan*/  status; int /*<<< orphan*/  channel; } ;
struct TYPE_11__ {TYPE_3__ chip_state_event; TYPE_2__ log_message; TYPE_1__ error_event; } ;
struct TYPE_12__ {TYPE_4__ leaf; } ;
struct kvaser_cmd {int id; TYPE_5__ u; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_CAN_ERROR_EVENT 130 
#define  CMD_CHIP_STATE_EVENT 129 
#define  CMD_LEAF_LOG_MESSAGE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_rx_error (struct kvaser_usb const*,struct kvaser_usb_err_summary*) ; 

__attribute__((used)) static void kvaser_usb_leaf_leaf_rx_error(const struct kvaser_usb *dev,
					  const struct kvaser_cmd *cmd)
{
	struct kvaser_usb_err_summary es = { };

	switch (cmd->id) {
	case CMD_CAN_ERROR_EVENT:
		es.channel = cmd->u.leaf.error_event.channel;
		es.status = cmd->u.leaf.error_event.status;
		es.txerr = cmd->u.leaf.error_event.tx_errors_count;
		es.rxerr = cmd->u.leaf.error_event.rx_errors_count;
		es.leaf.error_factor = cmd->u.leaf.error_event.error_factor;
		break;
	case CMD_LEAF_LOG_MESSAGE:
		es.channel = cmd->u.leaf.log_message.channel;
		es.status = cmd->u.leaf.log_message.data[0];
		es.txerr = cmd->u.leaf.log_message.data[2];
		es.rxerr = cmd->u.leaf.log_message.data[3];
		es.leaf.error_factor = cmd->u.leaf.log_message.data[1];
		break;
	case CMD_CHIP_STATE_EVENT:
		es.channel = cmd->u.leaf.chip_state_event.channel;
		es.status = cmd->u.leaf.chip_state_event.status;
		es.txerr = cmd->u.leaf.chip_state_event.tx_errors_count;
		es.rxerr = cmd->u.leaf.chip_state_event.rx_errors_count;
		es.leaf.error_factor = 0;
		break;
	default:
		dev_err(&dev->intf->dev, "Invalid cmd id (%d)\n", cmd->id);
		return;
	}

	kvaser_usb_leaf_rx_error(dev, &es);
}