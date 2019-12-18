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
typedef  int /*<<< orphan*/  u8 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct TYPE_6__ {scalar_t__ txerr; scalar_t__ rxerr; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_error; } ;
struct TYPE_5__ {int state; scalar_t__ restart_ms; TYPE_1__ can_stats; } ;
struct kvaser_usb_net_priv {TYPE_3__ bec; TYPE_2__ can; struct net_device* netdev; } ;
struct kvaser_err_frame_data {scalar_t__ tx_err_counter; scalar_t__ rx_err_counter; int /*<<< orphan*/  bus_status; } ;
struct can_frame {scalar_t__* data; scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;
struct can_berr_counter {scalar_t__ txerr; scalar_t__ rxerr; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_BUSERROR ; 
 int /*<<< orphan*/  CAN_ERR_RESTARTED ; 
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  CMD_STOP_CHIP_REQ ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  can_change_state (struct net_device*,struct can_frame*,int,int) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_bus_status_to_can_state (struct kvaser_usb_net_priv*,int /*<<< orphan*/ ,struct can_berr_counter*,int*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_send_simple_cmd_async (struct kvaser_usb_net_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static void
kvaser_usb_hydra_error_frame(struct kvaser_usb_net_priv *priv,
			     const struct kvaser_err_frame_data *err_frame_data,
			     ktime_t hwtstamp)
{
	struct net_device *netdev = priv->netdev;
	struct net_device_stats *stats = &netdev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	struct skb_shared_hwtstamps *shhwtstamps;
	struct can_berr_counter bec;
	enum can_state new_state, old_state;
	u8 bus_status;

	priv->can.can_stats.bus_error++;
	stats->rx_errors++;

	bus_status = err_frame_data->bus_status;
	bec.txerr = err_frame_data->tx_err_counter;
	bec.rxerr = err_frame_data->rx_err_counter;

	old_state = priv->can.state;
	kvaser_usb_hydra_bus_status_to_can_state(priv, bus_status, &bec,
						 &new_state);

	skb = alloc_can_err_skb(netdev, &cf);

	if (new_state != old_state) {
		if (skb) {
			enum can_state tx_state, rx_state;

			tx_state = (bec.txerr >= bec.rxerr) ?
					new_state : CAN_STATE_ERROR_ACTIVE;
			rx_state = (bec.txerr <= bec.rxerr) ?
					new_state : CAN_STATE_ERROR_ACTIVE;

			can_change_state(netdev, cf, tx_state, rx_state);

			if (priv->can.restart_ms &&
			    old_state >= CAN_STATE_BUS_OFF &&
			    new_state < CAN_STATE_BUS_OFF)
				cf->can_id |= CAN_ERR_RESTARTED;
		}

		if (new_state == CAN_STATE_BUS_OFF) {
			if (!priv->can.restart_ms)
				kvaser_usb_hydra_send_simple_cmd_async
						(priv, CMD_STOP_CHIP_REQ);

			can_bus_off(netdev);
		}
	}

	if (!skb) {
		stats->rx_dropped++;
		netdev_warn(netdev, "No memory left for err_skb\n");
		return;
	}

	shhwtstamps = skb_hwtstamps(skb);
	shhwtstamps->hwtstamp = hwtstamp;

	cf->can_id |= CAN_ERR_BUSERROR;
	cf->data[6] = bec.txerr;
	cf->data[7] = bec.rxerr;

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_rx(skb);

	priv->bec.txerr = bec.txerr;
	priv->bec.rxerr = bec.rxerr;
}