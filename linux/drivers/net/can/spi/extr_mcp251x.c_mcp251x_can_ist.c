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
struct spi_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {TYPE_3__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_off; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; } ;
struct TYPE_5__ {int state; scalar_t__ restart_ms; TYPE_1__ can_stats; } ;
struct mcp251x_priv {int force_quit; int tx_len; int /*<<< orphan*/  mcp_lock; TYPE_2__ can; struct net_device* net; struct spi_device* spi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int /*<<< orphan*/  CANINTF ; 
 int CANINTF_ERR ; 
 int CANINTF_ERRIF ; 
 int CANINTF_RX ; 
 int CANINTF_RX0IF ; 
 int CANINTF_RX1IF ; 
 int CANINTF_TX ; 
 int CAN_ERR_BUSOFF ; 
 int CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_RX_OVERFLOW ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int CAN_STATE_BUS_OFF ; 
#define  CAN_STATE_ERROR_ACTIVE 129 
 int CAN_STATE_ERROR_PASSIVE ; 
#define  CAN_STATE_ERROR_WARNING 128 
 int /*<<< orphan*/  EFLG ; 
 int EFLG_RX0OVR ; 
 int EFLG_RX1OVR ; 
 int EFLG_RXEP ; 
 int EFLG_RXWAR ; 
 int EFLG_TXBO ; 
 int EFLG_TXEP ; 
 int EFLG_TXWAR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp251x_error_skb (struct net_device*,int,int) ; 
 int /*<<< orphan*/  mcp251x_hw_rx (struct spi_device*,int) ; 
 int /*<<< orphan*/  mcp251x_hw_sleep (struct spi_device*) ; 
 scalar_t__ mcp251x_is_2510 (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_read_2regs (struct spi_device*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  mcp251x_write_bits (struct spi_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static irqreturn_t mcp251x_can_ist(int irq, void *dev_id)
{
	struct mcp251x_priv *priv = dev_id;
	struct spi_device *spi = priv->spi;
	struct net_device *net = priv->net;

	mutex_lock(&priv->mcp_lock);
	while (!priv->force_quit) {
		enum can_state new_state;
		u8 intf, eflag;
		u8 clear_intf = 0;
		int can_id = 0, data1 = 0;

		mcp251x_read_2regs(spi, CANINTF, &intf, &eflag);

		/* mask out flags we don't care about */
		intf &= CANINTF_RX | CANINTF_TX | CANINTF_ERR;

		/* receive buffer 0 */
		if (intf & CANINTF_RX0IF) {
			mcp251x_hw_rx(spi, 0);
			/* Free one buffer ASAP
			 * (The MCP2515/25625 does this automatically.)
			 */
			if (mcp251x_is_2510(spi))
				mcp251x_write_bits(spi, CANINTF,
						   CANINTF_RX0IF, 0x00);
		}

		/* receive buffer 1 */
		if (intf & CANINTF_RX1IF) {
			mcp251x_hw_rx(spi, 1);
			/* The MCP2515/25625 does this automatically. */
			if (mcp251x_is_2510(spi))
				clear_intf |= CANINTF_RX1IF;
		}

		/* any error or tx interrupt we need to clear? */
		if (intf & (CANINTF_ERR | CANINTF_TX))
			clear_intf |= intf & (CANINTF_ERR | CANINTF_TX);
		if (clear_intf)
			mcp251x_write_bits(spi, CANINTF, clear_intf, 0x00);

		if (eflag & (EFLG_RX0OVR | EFLG_RX1OVR))
			mcp251x_write_bits(spi, EFLG, eflag, 0x00);

		/* Update can state */
		if (eflag & EFLG_TXBO) {
			new_state = CAN_STATE_BUS_OFF;
			can_id |= CAN_ERR_BUSOFF;
		} else if (eflag & EFLG_TXEP) {
			new_state = CAN_STATE_ERROR_PASSIVE;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_TX_PASSIVE;
		} else if (eflag & EFLG_RXEP) {
			new_state = CAN_STATE_ERROR_PASSIVE;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_RX_PASSIVE;
		} else if (eflag & EFLG_TXWAR) {
			new_state = CAN_STATE_ERROR_WARNING;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_TX_WARNING;
		} else if (eflag & EFLG_RXWAR) {
			new_state = CAN_STATE_ERROR_WARNING;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_RX_WARNING;
		} else {
			new_state = CAN_STATE_ERROR_ACTIVE;
		}

		/* Update can state statistics */
		switch (priv->can.state) {
		case CAN_STATE_ERROR_ACTIVE:
			if (new_state >= CAN_STATE_ERROR_WARNING &&
			    new_state <= CAN_STATE_BUS_OFF)
				priv->can.can_stats.error_warning++;
			/* fall through */
		case CAN_STATE_ERROR_WARNING:
			if (new_state >= CAN_STATE_ERROR_PASSIVE &&
			    new_state <= CAN_STATE_BUS_OFF)
				priv->can.can_stats.error_passive++;
			break;
		default:
			break;
		}
		priv->can.state = new_state;

		if (intf & CANINTF_ERRIF) {
			/* Handle overflow counters */
			if (eflag & (EFLG_RX0OVR | EFLG_RX1OVR)) {
				if (eflag & EFLG_RX0OVR) {
					net->stats.rx_over_errors++;
					net->stats.rx_errors++;
				}
				if (eflag & EFLG_RX1OVR) {
					net->stats.rx_over_errors++;
					net->stats.rx_errors++;
				}
				can_id |= CAN_ERR_CRTL;
				data1 |= CAN_ERR_CRTL_RX_OVERFLOW;
			}
			mcp251x_error_skb(net, can_id, data1);
		}

		if (priv->can.state == CAN_STATE_BUS_OFF) {
			if (priv->can.restart_ms == 0) {
				priv->force_quit = 1;
				priv->can.can_stats.bus_off++;
				can_bus_off(net);
				mcp251x_hw_sleep(spi);
				break;
			}
		}

		if (intf == 0)
			break;

		if (intf & CANINTF_TX) {
			net->stats.tx_packets++;
			net->stats.tx_bytes += priv->tx_len - 1;
			can_led_event(net, CAN_LED_EVENT_TX);
			if (priv->tx_len) {
				can_get_echo_skb(net, 0);
				priv->tx_len = 0;
			}
			netif_wake_queue(net);
		}
	}
	mutex_unlock(&priv->mcp_lock);
	return IRQ_HANDLED;
}