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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  arbitration_lost; int /*<<< orphan*/  bus_error; } ;
struct TYPE_4__ {int state; TYPE_1__ can_stats; } ;
struct sun4ican_priv {TYPE_2__ can; scalar_t__ base; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {unsigned int* data; int can_id; scalar_t__ can_dlc; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_CRTL ; 
 unsigned int CAN_ERR_CRTL_RX_OVERFLOW ; 
 int CAN_ERR_LOSTARB ; 
 int CAN_ERR_PROT ; 
 unsigned int CAN_ERR_PROT_BIT ; 
 unsigned int CAN_ERR_PROT_FORM ; 
 unsigned int CAN_ERR_PROT_STUFF ; 
 int CAN_ERR_PROT_TX ; 
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SUN4I_CMD_CLEAR_OR_FLAG ; 
 int SUN4I_INT_ARB_LOST ; 
 int SUN4I_INT_BUS_ERR ; 
 int SUN4I_INT_DATA_OR ; 
 int SUN4I_INT_ERR_PASSIVE ; 
 int SUN4I_INT_ERR_WRN ; 
 scalar_t__ SUN4I_REG_ERRC_ADDR ; 
 scalar_t__ SUN4I_REG_STA_ADDR ; 
#define  SUN4I_STA_BIT_ERR 130 
 int SUN4I_STA_BUS_OFF ; 
 int SUN4I_STA_ERR_DIR ; 
 int SUN4I_STA_ERR_SEG_CODE ; 
 int SUN4I_STA_ERR_STA ; 
#define  SUN4I_STA_FORM_ERR 129 
 int SUN4I_STA_MASK_ERR ; 
#define  SUN4I_STA_STUFF_ERR 128 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  can_change_state (struct net_device*,struct can_frame*,int,int) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct sun4ican_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  set_normal_mode (struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 
 int /*<<< orphan*/  sun4i_can_write_cmdreg (struct sun4ican_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_can_err(struct net_device *dev, u8 isrc, u8 status)
{
	struct sun4ican_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	enum can_state state = priv->can.state;
	enum can_state rx_state, tx_state;
	unsigned int rxerr, txerr, errc;
	u32 ecc, alc;

	/* we don't skip if alloc fails because we want the stats anyhow */
	skb = alloc_can_err_skb(dev, &cf);

	errc = readl(priv->base + SUN4I_REG_ERRC_ADDR);
	rxerr = (errc >> 16) & 0xFF;
	txerr = errc & 0xFF;

	if (skb) {
		cf->data[6] = txerr;
		cf->data[7] = rxerr;
	}

	if (isrc & SUN4I_INT_DATA_OR) {
		/* data overrun interrupt */
		netdev_dbg(dev, "data overrun interrupt\n");
		if (likely(skb)) {
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		}
		stats->rx_over_errors++;
		stats->rx_errors++;

		/* reset the CAN IP by entering reset mode
		 * ignoring timeout error
		 */
		set_reset_mode(dev);
		set_normal_mode(dev);

		/* clear bit */
		sun4i_can_write_cmdreg(priv, SUN4I_CMD_CLEAR_OR_FLAG);
	}
	if (isrc & SUN4I_INT_ERR_WRN) {
		/* error warning interrupt */
		netdev_dbg(dev, "error warning interrupt\n");

		if (status & SUN4I_STA_BUS_OFF)
			state = CAN_STATE_BUS_OFF;
		else if (status & SUN4I_STA_ERR_STA)
			state = CAN_STATE_ERROR_WARNING;
		else
			state = CAN_STATE_ERROR_ACTIVE;
	}
	if (isrc & SUN4I_INT_BUS_ERR) {
		/* bus error interrupt */
		netdev_dbg(dev, "bus error interrupt\n");
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;

		if (likely(skb)) {
			ecc = readl(priv->base + SUN4I_REG_STA_ADDR);

			cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

			switch (ecc & SUN4I_STA_MASK_ERR) {
			case SUN4I_STA_BIT_ERR:
				cf->data[2] |= CAN_ERR_PROT_BIT;
				break;
			case SUN4I_STA_FORM_ERR:
				cf->data[2] |= CAN_ERR_PROT_FORM;
				break;
			case SUN4I_STA_STUFF_ERR:
				cf->data[2] |= CAN_ERR_PROT_STUFF;
				break;
			default:
				cf->data[3] = (ecc & SUN4I_STA_ERR_SEG_CODE)
					       >> 16;
				break;
			}
			/* error occurred during transmission? */
			if ((ecc & SUN4I_STA_ERR_DIR) == 0)
				cf->data[2] |= CAN_ERR_PROT_TX;
		}
	}
	if (isrc & SUN4I_INT_ERR_PASSIVE) {
		/* error passive interrupt */
		netdev_dbg(dev, "error passive interrupt\n");
		if (state == CAN_STATE_ERROR_PASSIVE)
			state = CAN_STATE_ERROR_WARNING;
		else
			state = CAN_STATE_ERROR_PASSIVE;
	}
	if (isrc & SUN4I_INT_ARB_LOST) {
		/* arbitration lost interrupt */
		netdev_dbg(dev, "arbitration lost interrupt\n");
		alc = readl(priv->base + SUN4I_REG_STA_ADDR);
		priv->can.can_stats.arbitration_lost++;
		stats->tx_errors++;
		if (likely(skb)) {
			cf->can_id |= CAN_ERR_LOSTARB;
			cf->data[0] = (alc >> 8) & 0x1f;
		}
	}

	if (state != priv->can.state) {
		tx_state = txerr >= rxerr ? state : 0;
		rx_state = txerr <= rxerr ? state : 0;

		if (likely(skb))
			can_change_state(dev, cf, tx_state, rx_state);
		else
			priv->can.state = state;
		if (state == CAN_STATE_BUS_OFF)
			can_bus_off(dev);
	}

	if (likely(skb)) {
		stats->rx_packets++;
		stats->rx_bytes += cf->can_dlc;
		netif_rx(skb);
	} else {
		return -ENOMEM;
	}

	return 0;
}