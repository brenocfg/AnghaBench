#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_8dev_rx_msg {int* data; } ;
struct TYPE_9__ {int txerr; int rxerr; } ;
struct TYPE_7__ {int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; int /*<<< orphan*/  bus_error; int /*<<< orphan*/  bus_off; } ;
struct TYPE_8__ {TYPE_1__ can_stats; void* state; } ;
struct usb_8dev_priv {TYPE_3__ bec; TYPE_4__* netdev; TYPE_2__ can; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct can_frame {int can_id; int* data; scalar_t__ can_dlc; } ;
struct TYPE_10__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_ERR_ACK ; 
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_BUSOFF ; 
 int CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_RX_OVERFLOW ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
 int CAN_ERR_PROT ; 
 int CAN_ERR_PROT_ACTIVE ; 
 int CAN_ERR_PROT_BIT0 ; 
 int CAN_ERR_PROT_BIT1 ; 
 int CAN_ERR_PROT_FORM ; 
 int CAN_ERR_PROT_LOC_CRC_SEQ ; 
 int CAN_ERR_PROT_STUFF ; 
 int CAN_ERR_PROT_TX ; 
 void* CAN_STATE_BUS_OFF ; 
 void* CAN_STATE_ERROR_ACTIVE ; 
 void* CAN_STATE_ERROR_PASSIVE ; 
 void* CAN_STATE_ERROR_WARNING ; 
 int USB_8DEV_RP_MASK ; 
#define  USB_8DEV_STATUSMSG_ACK 138 
#define  USB_8DEV_STATUSMSG_BIT0 137 
#define  USB_8DEV_STATUSMSG_BIT1 136 
#define  USB_8DEV_STATUSMSG_BUSHEAVY 135 
#define  USB_8DEV_STATUSMSG_BUSLIGHT 134 
#define  USB_8DEV_STATUSMSG_BUSOFF 133 
#define  USB_8DEV_STATUSMSG_CRC 132 
#define  USB_8DEV_STATUSMSG_FORM 131 
#define  USB_8DEV_STATUSMSG_OK 130 
#define  USB_8DEV_STATUSMSG_OVERRUN 129 
#define  USB_8DEV_STATUSMSG_STUFF 128 
 struct sk_buff* alloc_can_err_skb (TYPE_4__*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (TYPE_4__*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void usb_8dev_rx_err_msg(struct usb_8dev_priv *priv,
				struct usb_8dev_rx_msg *msg)
{
	struct can_frame *cf;
	struct sk_buff *skb;
	struct net_device_stats *stats = &priv->netdev->stats;

	/* Error message:
	 * byte 0: Status
	 * byte 1: bit   7: Receive Passive
	 * byte 1: bit 0-6: Receive Error Counter
	 * byte 2: Transmit Error Counter
	 * byte 3: Always 0 (maybe reserved for future use)
	 */

	u8 state = msg->data[0];
	u8 rxerr = msg->data[1] & USB_8DEV_RP_MASK;
	u8 txerr = msg->data[2];
	int rx_errors = 0;
	int tx_errors = 0;

	skb = alloc_can_err_skb(priv->netdev, &cf);
	if (!skb)
		return;

	switch (state) {
	case USB_8DEV_STATUSMSG_OK:
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		cf->can_id |= CAN_ERR_PROT;
		cf->data[2] = CAN_ERR_PROT_ACTIVE;
		break;
	case USB_8DEV_STATUSMSG_BUSOFF:
		priv->can.state = CAN_STATE_BUS_OFF;
		cf->can_id |= CAN_ERR_BUSOFF;
		priv->can.can_stats.bus_off++;
		can_bus_off(priv->netdev);
		break;
	case USB_8DEV_STATUSMSG_OVERRUN:
	case USB_8DEV_STATUSMSG_BUSLIGHT:
	case USB_8DEV_STATUSMSG_BUSHEAVY:
		cf->can_id |= CAN_ERR_CRTL;
		break;
	default:
		priv->can.state = CAN_STATE_ERROR_WARNING;
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
		priv->can.can_stats.bus_error++;
		break;
	}

	switch (state) {
	case USB_8DEV_STATUSMSG_OK:
	case USB_8DEV_STATUSMSG_BUSOFF:
		break;
	case USB_8DEV_STATUSMSG_ACK:
		cf->can_id |= CAN_ERR_ACK;
		tx_errors = 1;
		break;
	case USB_8DEV_STATUSMSG_CRC:
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		rx_errors = 1;
		break;
	case USB_8DEV_STATUSMSG_BIT0:
		cf->data[2] |= CAN_ERR_PROT_BIT0;
		tx_errors = 1;
		break;
	case USB_8DEV_STATUSMSG_BIT1:
		cf->data[2] |= CAN_ERR_PROT_BIT1;
		tx_errors = 1;
		break;
	case USB_8DEV_STATUSMSG_FORM:
		cf->data[2] |= CAN_ERR_PROT_FORM;
		rx_errors = 1;
		break;
	case USB_8DEV_STATUSMSG_STUFF:
		cf->data[2] |= CAN_ERR_PROT_STUFF;
		rx_errors = 1;
		break;
	case USB_8DEV_STATUSMSG_OVERRUN:
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		rx_errors = 1;
		break;
	case USB_8DEV_STATUSMSG_BUSLIGHT:
		priv->can.state = CAN_STATE_ERROR_WARNING;
		cf->data[1] = (txerr > rxerr) ?
			CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		priv->can.can_stats.error_warning++;
		break;
	case USB_8DEV_STATUSMSG_BUSHEAVY:
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		cf->data[1] = (txerr > rxerr) ?
			CAN_ERR_CRTL_TX_PASSIVE :
			CAN_ERR_CRTL_RX_PASSIVE;
		priv->can.can_stats.error_passive++;
		break;
	default:
		netdev_warn(priv->netdev,
			    "Unknown status/error message (%d)\n", state);
		break;
	}

	if (tx_errors) {
		cf->data[2] |= CAN_ERR_PROT_TX;
		stats->tx_errors++;
	}

	if (rx_errors)
		stats->rx_errors++;

	cf->data[6] = txerr;
	cf->data[7] = rxerr;

	priv->bec.txerr = txerr;
	priv->bec.rxerr = rxerr;

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_rx(skb);
}