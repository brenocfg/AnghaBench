#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  other_ch_status; } ;
struct kvaser_usb_err_summary {int channel; TYPE_2__ usbcan; int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; int /*<<< orphan*/  status; } ;
struct kvaser_usb {TYPE_6__* intf; int /*<<< orphan*/  nchannels; } ;
struct TYPE_9__ {int /*<<< orphan*/  status_ch0; int /*<<< orphan*/  rx_errors_count_ch1; int /*<<< orphan*/  tx_errors_count_ch1; int /*<<< orphan*/  status_ch1; int /*<<< orphan*/  rx_errors_count_ch0; int /*<<< orphan*/  tx_errors_count_ch0; } ;
struct TYPE_7__ {int channel; int /*<<< orphan*/  rx_errors_count; int /*<<< orphan*/  tx_errors_count; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {TYPE_3__ error_event; TYPE_1__ chip_state_event; } ;
struct TYPE_11__ {TYPE_4__ usbcan; } ;
struct kvaser_cmd {int id; TYPE_5__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_CAN_ERROR_EVENT 129 
#define  CMD_CHIP_STATE_EVENT 128 
 int /*<<< orphan*/  MAX_USBCAN_NET_DEVICES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_usbcan_conditionally_rx_error (struct kvaser_usb const*,struct kvaser_usb_err_summary*) ; 

__attribute__((used)) static void kvaser_usb_leaf_usbcan_rx_error(const struct kvaser_usb *dev,
					    const struct kvaser_cmd *cmd)
{
	struct kvaser_usb_err_summary es = { };

	switch (cmd->id) {
	/* Sometimes errors are sent as unsolicited chip state events */
	case CMD_CHIP_STATE_EVENT:
		es.channel = cmd->u.usbcan.chip_state_event.channel;
		es.status = cmd->u.usbcan.chip_state_event.status;
		es.txerr = cmd->u.usbcan.chip_state_event.tx_errors_count;
		es.rxerr = cmd->u.usbcan.chip_state_event.rx_errors_count;
		kvaser_usb_leaf_usbcan_conditionally_rx_error(dev, &es);
		break;

	case CMD_CAN_ERROR_EVENT:
		es.channel = 0;
		es.status = cmd->u.usbcan.error_event.status_ch0;
		es.txerr = cmd->u.usbcan.error_event.tx_errors_count_ch0;
		es.rxerr = cmd->u.usbcan.error_event.rx_errors_count_ch0;
		es.usbcan.other_ch_status =
			cmd->u.usbcan.error_event.status_ch1;
		kvaser_usb_leaf_usbcan_conditionally_rx_error(dev, &es);

		/* The USBCAN firmware supports up to 2 channels.
		 * Now that ch0 was checked, check if ch1 has any errors.
		 */
		if (dev->nchannels == MAX_USBCAN_NET_DEVICES) {
			es.channel = 1;
			es.status = cmd->u.usbcan.error_event.status_ch1;
			es.txerr =
				cmd->u.usbcan.error_event.tx_errors_count_ch1;
			es.rxerr =
				cmd->u.usbcan.error_event.rx_errors_count_ch1;
			es.usbcan.other_ch_status =
				cmd->u.usbcan.error_event.status_ch0;
			kvaser_usb_leaf_usbcan_conditionally_rx_error(dev, &es);
		}
		break;

	default:
		dev_err(&dev->intf->dev, "Invalid cmd id (%d)\n", cmd->id);
	}
}