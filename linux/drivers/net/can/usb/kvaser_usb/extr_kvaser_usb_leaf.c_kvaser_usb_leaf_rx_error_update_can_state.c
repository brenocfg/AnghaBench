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
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_16__ {int txerr; int rxerr; } ;
struct TYPE_14__ {int /*<<< orphan*/  bus_error; int /*<<< orphan*/  restarts; } ;
struct TYPE_15__ {int state; TYPE_5__ can_stats; scalar_t__ restart_ms; } ;
struct kvaser_usb_net_priv {TYPE_7__ bec; TYPE_6__ can; TYPE_8__* netdev; struct kvaser_usb* dev; } ;
struct TYPE_13__ {int error_state; } ;
struct TYPE_12__ {int /*<<< orphan*/  error_factor; } ;
struct kvaser_usb_err_summary {int status; int txerr; int rxerr; TYPE_4__ usbcan; TYPE_3__ leaf; } ;
struct TYPE_10__ {int family; } ;
struct TYPE_11__ {TYPE_1__ leaf; } ;
struct kvaser_usb {TYPE_2__ card_data; } ;
struct can_frame {int dummy; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;
struct TYPE_17__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
#define  KVASER_LEAF 129 
#define  KVASER_USBCAN 128 
 int M16C_STATE_BUS_ERROR ; 
 int M16C_STATE_BUS_OFF ; 
 int M16C_STATE_BUS_PASSIVE ; 
 int M16C_STATE_BUS_RESET ; 
 int USBCAN_ERROR_STATE_BUSERROR ; 
 int USBCAN_ERROR_STATE_RX_ERROR ; 
 int USBCAN_ERROR_STATE_TX_ERROR ; 
 int /*<<< orphan*/  can_change_state (TYPE_8__*,struct can_frame*,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_8__*,char*,int) ; 

__attribute__((used)) static void
kvaser_usb_leaf_rx_error_update_can_state(struct kvaser_usb_net_priv *priv,
					const struct kvaser_usb_err_summary *es,
					struct can_frame *cf)
{
	struct kvaser_usb *dev = priv->dev;
	struct net_device_stats *stats = &priv->netdev->stats;
	enum can_state cur_state, new_state, tx_state, rx_state;

	netdev_dbg(priv->netdev, "Error status: 0x%02x\n", es->status);

	new_state = priv->can.state;
	cur_state = priv->can.state;

	if (es->status & (M16C_STATE_BUS_OFF | M16C_STATE_BUS_RESET)) {
		new_state = CAN_STATE_BUS_OFF;
	} else if (es->status & M16C_STATE_BUS_PASSIVE) {
		new_state = CAN_STATE_ERROR_PASSIVE;
	} else if (es->status & M16C_STATE_BUS_ERROR) {
		/* Guard against spurious error events after a busoff */
		if (cur_state < CAN_STATE_BUS_OFF) {
			if (es->txerr >= 128 || es->rxerr >= 128)
				new_state = CAN_STATE_ERROR_PASSIVE;
			else if (es->txerr >= 96 || es->rxerr >= 96)
				new_state = CAN_STATE_ERROR_WARNING;
			else if (cur_state > CAN_STATE_ERROR_ACTIVE)
				new_state = CAN_STATE_ERROR_ACTIVE;
		}
	}

	if (!es->status)
		new_state = CAN_STATE_ERROR_ACTIVE;

	if (new_state != cur_state) {
		tx_state = (es->txerr >= es->rxerr) ? new_state : 0;
		rx_state = (es->txerr <= es->rxerr) ? new_state : 0;

		can_change_state(priv->netdev, cf, tx_state, rx_state);
	}

	if (priv->can.restart_ms &&
	    cur_state >= CAN_STATE_BUS_OFF &&
	    new_state < CAN_STATE_BUS_OFF)
		priv->can.can_stats.restarts++;

	switch (dev->card_data.leaf.family) {
	case KVASER_LEAF:
		if (es->leaf.error_factor) {
			priv->can.can_stats.bus_error++;
			stats->rx_errors++;
		}
		break;
	case KVASER_USBCAN:
		if (es->usbcan.error_state & USBCAN_ERROR_STATE_TX_ERROR)
			stats->tx_errors++;
		if (es->usbcan.error_state & USBCAN_ERROR_STATE_RX_ERROR)
			stats->rx_errors++;
		if (es->usbcan.error_state & USBCAN_ERROR_STATE_BUSERROR)
			priv->can.can_stats.bus_error++;
		break;
	}

	priv->bec.txerr = es->txerr;
	priv->bec.rxerr = es->rxerr;
}