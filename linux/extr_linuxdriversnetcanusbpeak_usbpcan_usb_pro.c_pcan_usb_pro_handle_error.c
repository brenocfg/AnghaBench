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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  error_warning; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  bus_off; } ;
struct TYPE_5__ {int state; TYPE_1__ can_stats; } ;
struct peak_usb_device {TYPE_2__ can; struct net_device* netdev; } ;
struct pcan_usb_pro_rxstatus {int channel; int /*<<< orphan*/  ts32; int /*<<< orphan*/  err_frm; int /*<<< orphan*/  status; } ;
struct pcan_usb_pro_interface {int /*<<< orphan*/  time_ref; struct peak_usb_device** dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {TYPE_3__ stats; } ;
struct can_frame {int* data; scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_BUSOFF ; 
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_RX_OVERFLOW ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
 int /*<<< orphan*/  CAN_ERR_PROT ; 
 int CAN_ERR_PROT_OVERLOAD ; 
#define  CAN_STATE_BUS_OFF 131 
#define  CAN_STATE_ERROR_ACTIVE 130 
#define  CAN_STATE_ERROR_PASSIVE 129 
#define  CAN_STATE_ERROR_WARNING 128 
 int CAN_STATE_MAX ; 
 int ENOMEM ; 
 int const PCAN_USBPRO_STATUS_BUS ; 
 int const PCAN_USBPRO_STATUS_ERROR ; 
 int const PCAN_USBPRO_STATUS_OVERRUN ; 
 int const PCAN_USBPRO_STATUS_QOVERRUN ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  peak_usb_get_ts_time (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static int pcan_usb_pro_handle_error(struct pcan_usb_pro_interface *usb_if,
				     struct pcan_usb_pro_rxstatus *er)
{
	const u16 raw_status = le16_to_cpu(er->status);
	const unsigned int ctrl_idx = (er->channel >> 4) & 0x0f;
	struct peak_usb_device *dev = usb_if->dev[ctrl_idx];
	struct net_device *netdev = dev->netdev;
	struct can_frame *can_frame;
	enum can_state new_state = CAN_STATE_ERROR_ACTIVE;
	u8 err_mask = 0;
	struct sk_buff *skb;
	struct skb_shared_hwtstamps *hwts;

	/* nothing should be sent while in BUS_OFF state */
	if (dev->can.state == CAN_STATE_BUS_OFF)
		return 0;

	if (!raw_status) {
		/* no error bit (back to active state) */
		dev->can.state = CAN_STATE_ERROR_ACTIVE;
		return 0;
	}

	if (raw_status & (PCAN_USBPRO_STATUS_OVERRUN |
			  PCAN_USBPRO_STATUS_QOVERRUN)) {
		/* trick to bypass next comparison and process other errors */
		new_state = CAN_STATE_MAX;
	}

	if (raw_status & PCAN_USBPRO_STATUS_BUS) {
		new_state = CAN_STATE_BUS_OFF;
	} else if (raw_status & PCAN_USBPRO_STATUS_ERROR) {
		u32 rx_err_cnt = (le32_to_cpu(er->err_frm) & 0x00ff0000) >> 16;
		u32 tx_err_cnt = (le32_to_cpu(er->err_frm) & 0xff000000) >> 24;

		if (rx_err_cnt > 127)
			err_mask |= CAN_ERR_CRTL_RX_PASSIVE;
		else if (rx_err_cnt > 96)
			err_mask |= CAN_ERR_CRTL_RX_WARNING;

		if (tx_err_cnt > 127)
			err_mask |= CAN_ERR_CRTL_TX_PASSIVE;
		else if (tx_err_cnt > 96)
			err_mask |= CAN_ERR_CRTL_TX_WARNING;

		if (err_mask & (CAN_ERR_CRTL_RX_WARNING |
				CAN_ERR_CRTL_TX_WARNING))
			new_state = CAN_STATE_ERROR_WARNING;
		else if (err_mask & (CAN_ERR_CRTL_RX_PASSIVE |
				     CAN_ERR_CRTL_TX_PASSIVE))
			new_state = CAN_STATE_ERROR_PASSIVE;
	}

	/* donot post any error if current state didn't change */
	if (dev->can.state == new_state)
		return 0;

	/* allocate an skb to store the error frame */
	skb = alloc_can_err_skb(netdev, &can_frame);
	if (!skb)
		return -ENOMEM;

	switch (new_state) {
	case CAN_STATE_BUS_OFF:
		can_frame->can_id |= CAN_ERR_BUSOFF;
		dev->can.can_stats.bus_off++;
		can_bus_off(netdev);
		break;

	case CAN_STATE_ERROR_PASSIVE:
		can_frame->can_id |= CAN_ERR_CRTL;
		can_frame->data[1] |= err_mask;
		dev->can.can_stats.error_passive++;
		break;

	case CAN_STATE_ERROR_WARNING:
		can_frame->can_id |= CAN_ERR_CRTL;
		can_frame->data[1] |= err_mask;
		dev->can.can_stats.error_warning++;
		break;

	case CAN_STATE_ERROR_ACTIVE:
		break;

	default:
		/* CAN_STATE_MAX (trick to handle other errors) */
		if (raw_status & PCAN_USBPRO_STATUS_OVERRUN) {
			can_frame->can_id |= CAN_ERR_PROT;
			can_frame->data[2] |= CAN_ERR_PROT_OVERLOAD;
			netdev->stats.rx_over_errors++;
			netdev->stats.rx_errors++;
		}

		if (raw_status & PCAN_USBPRO_STATUS_QOVERRUN) {
			can_frame->can_id |= CAN_ERR_CRTL;
			can_frame->data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
			netdev->stats.rx_over_errors++;
			netdev->stats.rx_errors++;
		}

		new_state = CAN_STATE_ERROR_ACTIVE;
		break;
	}

	dev->can.state = new_state;

	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_time(&usb_if->time_ref, le32_to_cpu(er->ts32), &hwts->hwtstamp);
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += can_frame->can_dlc;
	netif_rx(skb);

	return 0;
}