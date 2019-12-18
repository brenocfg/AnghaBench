#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_12__ {int txerr; int rxerr; } ;
struct TYPE_10__ {int /*<<< orphan*/  bus_error; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; int /*<<< orphan*/  bus_off; } ;
struct TYPE_11__ {scalar_t__ state; TYPE_3__ can_stats; } ;
struct esd_usb2_net_priv {int old_state; TYPE_5__ bec; TYPE_4__ can; TYPE_6__* netdev; } ;
struct TYPE_8__ {int* data; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_1__ rx; } ;
struct esd_usb2_msg {TYPE_2__ msg; } ;
struct can_frame {int can_id; int* data; scalar_t__ can_dlc; } ;
struct TYPE_13__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_BUSOFF ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_PROT ; 
 int CAN_ERR_PROT_BIT ; 
 int CAN_ERR_PROT_FORM ; 
 int CAN_ERR_PROT_STUFF ; 
 int CAN_ERR_PROT_TX ; 
 scalar_t__ CAN_STATE_BUS_OFF ; 
 scalar_t__ CAN_STATE_ERROR_ACTIVE ; 
 scalar_t__ CAN_STATE_ERROR_PASSIVE ; 
 scalar_t__ CAN_STATE_ERROR_WARNING ; 
#define  ESD_BUSSTATE_BUSOFF 133 
#define  ESD_BUSSTATE_ERRPASSIVE 132 
 int ESD_BUSSTATE_MASK ; 
#define  ESD_BUSSTATE_WARN 131 
 scalar_t__ ESD_EV_CAN_ERROR_EXT ; 
 scalar_t__ ESD_IDMASK ; 
#define  SJA1000_ECC_BIT 130 
 int SJA1000_ECC_DIR ; 
#define  SJA1000_ECC_FORM 129 
 int SJA1000_ECC_MASK ; 
 int SJA1000_ECC_SEG ; 
#define  SJA1000_ECC_STUFF 128 
 struct sk_buff* alloc_can_err_skb (TYPE_6__*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (TYPE_6__*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void esd_usb2_rx_event(struct esd_usb2_net_priv *priv,
			      struct esd_usb2_msg *msg)
{
	struct net_device_stats *stats = &priv->netdev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	u32 id = le32_to_cpu(msg->msg.rx.id) & ESD_IDMASK;

	if (id == ESD_EV_CAN_ERROR_EXT) {
		u8 state = msg->msg.rx.data[0];
		u8 ecc = msg->msg.rx.data[1];
		u8 txerr = msg->msg.rx.data[2];
		u8 rxerr = msg->msg.rx.data[3];

		skb = alloc_can_err_skb(priv->netdev, &cf);
		if (skb == NULL) {
			stats->rx_dropped++;
			return;
		}

		if (state != priv->old_state) {
			priv->old_state = state;

			switch (state & ESD_BUSSTATE_MASK) {
			case ESD_BUSSTATE_BUSOFF:
				priv->can.state = CAN_STATE_BUS_OFF;
				cf->can_id |= CAN_ERR_BUSOFF;
				priv->can.can_stats.bus_off++;
				can_bus_off(priv->netdev);
				break;
			case ESD_BUSSTATE_WARN:
				priv->can.state = CAN_STATE_ERROR_WARNING;
				priv->can.can_stats.error_warning++;
				break;
			case ESD_BUSSTATE_ERRPASSIVE:
				priv->can.state = CAN_STATE_ERROR_PASSIVE;
				priv->can.can_stats.error_passive++;
				break;
			default:
				priv->can.state = CAN_STATE_ERROR_ACTIVE;
				break;
			}
		} else {
			priv->can.can_stats.bus_error++;
			stats->rx_errors++;

			cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

			switch (ecc & SJA1000_ECC_MASK) {
			case SJA1000_ECC_BIT:
				cf->data[2] |= CAN_ERR_PROT_BIT;
				break;
			case SJA1000_ECC_FORM:
				cf->data[2] |= CAN_ERR_PROT_FORM;
				break;
			case SJA1000_ECC_STUFF:
				cf->data[2] |= CAN_ERR_PROT_STUFF;
				break;
			default:
				cf->data[3] = ecc & SJA1000_ECC_SEG;
				break;
			}

			/* Error occurred during transmission? */
			if (!(ecc & SJA1000_ECC_DIR))
				cf->data[2] |= CAN_ERR_PROT_TX;

			if (priv->can.state == CAN_STATE_ERROR_WARNING ||
			    priv->can.state == CAN_STATE_ERROR_PASSIVE) {
				cf->data[1] = (txerr > rxerr) ?
					CAN_ERR_CRTL_TX_PASSIVE :
					CAN_ERR_CRTL_RX_PASSIVE;
			}
			cf->data[6] = txerr;
			cf->data[7] = rxerr;
		}

		priv->bec.txerr = txerr;
		priv->bec.rxerr = rxerr;

		stats->rx_packets++;
		stats->rx_bytes += cf->can_dlc;
		netif_rx(skb);
	}
}