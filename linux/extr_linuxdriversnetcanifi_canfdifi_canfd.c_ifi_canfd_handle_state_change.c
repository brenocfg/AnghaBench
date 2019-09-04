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
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_off; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; } ;
struct TYPE_4__ {int state; TYPE_1__ can_stats; } ;
struct ifi_canfd_priv {TYPE_2__ can; } ;
struct can_frame {int* data; scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;
struct can_berr_counter {int txerr; int rxerr; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_BUSOFF ; 
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
#define  CAN_STATE_BUS_OFF 131 
#define  CAN_STATE_ERROR_ACTIVE 130 
#define  CAN_STATE_ERROR_PASSIVE 129 
#define  CAN_STATE_ERROR_WARNING 128 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  ifi_canfd_get_berr_counter (struct net_device*,struct can_berr_counter*) ; 
 int /*<<< orphan*/  ifi_canfd_irq_enable (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ifi_canfd_handle_state_change(struct net_device *ndev,
					 enum can_state new_state)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	struct can_berr_counter bec;

	switch (new_state) {
	case CAN_STATE_ERROR_ACTIVE:
		/* error active state */
		priv->can.can_stats.error_warning++;
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		break;
	case CAN_STATE_ERROR_WARNING:
		/* error warning state */
		priv->can.can_stats.error_warning++;
		priv->can.state = CAN_STATE_ERROR_WARNING;
		break;
	case CAN_STATE_ERROR_PASSIVE:
		/* error passive state */
		priv->can.can_stats.error_passive++;
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		break;
	case CAN_STATE_BUS_OFF:
		/* bus-off state */
		priv->can.state = CAN_STATE_BUS_OFF;
		ifi_canfd_irq_enable(ndev, 0);
		priv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		break;
	default:
		break;
	}

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(ndev, &cf);
	if (unlikely(!skb))
		return 0;

	ifi_canfd_get_berr_counter(ndev, &bec);

	switch (new_state) {
	case CAN_STATE_ERROR_WARNING:
		/* error warning state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = (bec.txerr > bec.rxerr) ?
			CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		break;
	case CAN_STATE_ERROR_PASSIVE:
		/* error passive state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		if (bec.txerr > 127)
			cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		break;
	case CAN_STATE_BUS_OFF:
		/* bus-off state */
		cf->can_id |= CAN_ERR_BUSOFF;
		break;
	default:
		break;
	}

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_receive_skb(skb);

	return 1;
}