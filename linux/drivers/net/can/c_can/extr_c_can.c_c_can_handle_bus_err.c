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
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int can_id; scalar_t__ can_dlc; int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_error; } ;
struct TYPE_4__ {int ctrlmode; TYPE_1__ can_stats; } ;
struct c_can_priv {TYPE_2__ can; } ;
typedef  enum c_can_lec_type { ____Placeholder_c_can_lec_type } c_can_lec_type ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_PROT ; 
 int /*<<< orphan*/  CAN_ERR_PROT_BIT0 ; 
 int /*<<< orphan*/  CAN_ERR_PROT_BIT1 ; 
 int /*<<< orphan*/  CAN_ERR_PROT_FORM ; 
 int /*<<< orphan*/  CAN_ERR_PROT_LOC_ACK ; 
 int /*<<< orphan*/  CAN_ERR_PROT_LOC_CRC_SEQ ; 
 int /*<<< orphan*/  CAN_ERR_PROT_STUFF ; 
#define  LEC_ACK_ERROR 133 
#define  LEC_BIT0_ERROR 132 
#define  LEC_BIT1_ERROR 131 
#define  LEC_CRC_ERROR 130 
#define  LEC_FORM_ERROR 129 
 int LEC_NO_ERROR ; 
#define  LEC_STUFF_ERROR 128 
 int LEC_UNUSED ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int c_can_handle_bus_err(struct net_device *dev,
				enum c_can_lec_type lec_type)
{
	struct c_can_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;

	/*
	 * early exit if no lec update or no error.
	 * no lec update means that no CAN bus event has been detected
	 * since CPU wrote 0x7 value to status reg.
	 */
	if (lec_type == LEC_UNUSED || lec_type == LEC_NO_ERROR)
		return 0;

	if (!(priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING))
		return 0;

	/* common for all type of bus errors */
	priv->can.can_stats.bus_error++;
	stats->rx_errors++;

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(dev, &cf);
	if (unlikely(!skb))
		return 0;

	/*
	 * check for 'last error code' which tells us the
	 * type of the last error to occur on the CAN bus
	 */
	cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

	switch (lec_type) {
	case LEC_STUFF_ERROR:
		netdev_dbg(dev, "stuff error\n");
		cf->data[2] |= CAN_ERR_PROT_STUFF;
		break;
	case LEC_FORM_ERROR:
		netdev_dbg(dev, "form error\n");
		cf->data[2] |= CAN_ERR_PROT_FORM;
		break;
	case LEC_ACK_ERROR:
		netdev_dbg(dev, "ack error\n");
		cf->data[3] = CAN_ERR_PROT_LOC_ACK;
		break;
	case LEC_BIT1_ERROR:
		netdev_dbg(dev, "bit1 error\n");
		cf->data[2] |= CAN_ERR_PROT_BIT1;
		break;
	case LEC_BIT0_ERROR:
		netdev_dbg(dev, "bit0 error\n");
		cf->data[2] |= CAN_ERR_PROT_BIT0;
		break;
	case LEC_CRC_ERROR:
		netdev_dbg(dev, "CRC error\n");
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		break;
	default:
		break;
	}

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_receive_skb(skb);
	return 1;
}