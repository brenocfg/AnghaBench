#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct TYPE_15__ {int /*<<< orphan*/  bus_error; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; int /*<<< orphan*/  bus_off; } ;
struct TYPE_16__ {scalar_t__ state; TYPE_6__ can_stats; } ;
struct ems_usb {TYPE_7__ can; TYPE_8__* netdev; } ;
struct TYPE_10__ {int ecc; int txerr; int rxerr; } ;
struct TYPE_11__ {TYPE_1__ sja1000; } ;
struct TYPE_12__ {TYPE_2__ regs; } ;
struct TYPE_13__ {TYPE_3__ cc; } ;
struct TYPE_14__ {int can_state; TYPE_4__ error; } ;
struct ems_cpc_msg {scalar_t__ type; TYPE_5__ msg; } ;
struct can_frame {int can_id; int* data; scalar_t__ can_dlc; } ;
struct TYPE_17__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_BUSOFF ; 
 int CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_RX_OVERFLOW ; 
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
 scalar_t__ CPC_MSG_TYPE_CAN_FRAME_ERROR ; 
 scalar_t__ CPC_MSG_TYPE_CAN_STATE ; 
 scalar_t__ CPC_MSG_TYPE_OVERRUN ; 
#define  SJA1000_ECC_BIT 130 
 int SJA1000_ECC_DIR ; 
#define  SJA1000_ECC_FORM 129 
 int SJA1000_ECC_MASK ; 
 int SJA1000_ECC_SEG ; 
#define  SJA1000_ECC_STUFF 128 
 int SJA1000_SR_BS ; 
 int SJA1000_SR_ES ; 
 struct sk_buff* alloc_can_err_skb (TYPE_8__*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (TYPE_8__*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void ems_usb_rx_err(struct ems_usb *dev, struct ems_cpc_msg *msg)
{
	struct can_frame *cf;
	struct sk_buff *skb;
	struct net_device_stats *stats = &dev->netdev->stats;

	skb = alloc_can_err_skb(dev->netdev, &cf);
	if (skb == NULL)
		return;

	if (msg->type == CPC_MSG_TYPE_CAN_STATE) {
		u8 state = msg->msg.can_state;

		if (state & SJA1000_SR_BS) {
			dev->can.state = CAN_STATE_BUS_OFF;
			cf->can_id |= CAN_ERR_BUSOFF;

			dev->can.can_stats.bus_off++;
			can_bus_off(dev->netdev);
		} else if (state & SJA1000_SR_ES) {
			dev->can.state = CAN_STATE_ERROR_WARNING;
			dev->can.can_stats.error_warning++;
		} else {
			dev->can.state = CAN_STATE_ERROR_ACTIVE;
			dev->can.can_stats.error_passive++;
		}
	} else if (msg->type == CPC_MSG_TYPE_CAN_FRAME_ERROR) {
		u8 ecc = msg->msg.error.cc.regs.sja1000.ecc;
		u8 txerr = msg->msg.error.cc.regs.sja1000.txerr;
		u8 rxerr = msg->msg.error.cc.regs.sja1000.rxerr;

		/* bus error interrupt */
		dev->can.can_stats.bus_error++;
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
		if ((ecc & SJA1000_ECC_DIR) == 0)
			cf->data[2] |= CAN_ERR_PROT_TX;

		if (dev->can.state == CAN_STATE_ERROR_WARNING ||
		    dev->can.state == CAN_STATE_ERROR_PASSIVE) {
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (txerr > rxerr) ?
			    CAN_ERR_CRTL_TX_PASSIVE : CAN_ERR_CRTL_RX_PASSIVE;
		}
	} else if (msg->type == CPC_MSG_TYPE_OVERRUN) {
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

		stats->rx_over_errors++;
		stats->rx_errors++;
	}

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_rx(skb);
}