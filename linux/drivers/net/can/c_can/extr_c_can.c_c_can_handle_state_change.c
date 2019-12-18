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
struct can_frame {int* data; scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;
struct can_berr_counter {int txerr; int rxerr; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_off; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; } ;
struct TYPE_4__ {TYPE_1__ can_stats; int /*<<< orphan*/  state; } ;
struct c_can_priv {unsigned int (* read_reg ) (struct c_can_priv*,int /*<<< orphan*/ ) ;TYPE_2__ can; } ;
typedef  enum c_can_bus_error_types { ____Placeholder_c_can_bus_error_types } c_can_bus_error_types ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_BUSOFF ; 
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_ACTIVE ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
 int /*<<< orphan*/  CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_PASSIVE ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_WARNING ; 
#define  C_CAN_BUS_OFF 131 
#define  C_CAN_ERROR_PASSIVE 130 
#define  C_CAN_ERROR_WARNING 129 
 int /*<<< orphan*/  C_CAN_ERR_CNT_REG ; 
#define  C_CAN_NO_ERROR 128 
 unsigned int ERR_CNT_RP_MASK ; 
 unsigned int ERR_CNT_RP_SHIFT ; 
 int /*<<< orphan*/  __c_can_get_berr_counter (struct net_device*,struct can_berr_counter*) ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 unsigned int stub1 (struct c_can_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int c_can_handle_state_change(struct net_device *dev,
				enum c_can_bus_error_types error_type)
{
	unsigned int reg_err_counter;
	unsigned int rx_err_passive;
	struct c_can_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	struct can_berr_counter bec;

	switch (error_type) {
	case C_CAN_NO_ERROR:
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		break;
	case C_CAN_ERROR_WARNING:
		/* error warning state */
		priv->can.can_stats.error_warning++;
		priv->can.state = CAN_STATE_ERROR_WARNING;
		break;
	case C_CAN_ERROR_PASSIVE:
		/* error passive state */
		priv->can.can_stats.error_passive++;
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		break;
	case C_CAN_BUS_OFF:
		/* bus-off state */
		priv->can.state = CAN_STATE_BUS_OFF;
		priv->can.can_stats.bus_off++;
		break;
	default:
		break;
	}

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(dev, &cf);
	if (unlikely(!skb))
		return 0;

	__c_can_get_berr_counter(dev, &bec);
	reg_err_counter = priv->read_reg(priv, C_CAN_ERR_CNT_REG);
	rx_err_passive = (reg_err_counter & ERR_CNT_RP_MASK) >>
				ERR_CNT_RP_SHIFT;

	switch (error_type) {
	case C_CAN_NO_ERROR:
		/* error warning state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_ACTIVE;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		break;
	case C_CAN_ERROR_WARNING:
		/* error warning state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = (bec.txerr > bec.rxerr) ?
			CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;

		break;
	case C_CAN_ERROR_PASSIVE:
		/* error passive state */
		cf->can_id |= CAN_ERR_CRTL;
		if (rx_err_passive)
			cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		if (bec.txerr > 127)
			cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;

		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		break;
	case C_CAN_BUS_OFF:
		/* bus-off state */
		cf->can_id |= CAN_ERR_BUSOFF;
		can_bus_off(dev);
		break;
	default:
		break;
	}

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_receive_skb(skb);

	return 1;
}