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
struct TYPE_3__ {int /*<<< orphan*/  bus_error; int /*<<< orphan*/  bus_off; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; } ;
struct TYPE_4__ {TYPE_1__ can_stats; int /*<<< orphan*/  state; } ;
struct ti_hecc_priv {TYPE_2__ can; int /*<<< orphan*/  ndev; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int can_id; scalar_t__ can_dlc; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_BUSOFF ; 
 int CAN_ERR_CRTL ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_PASSIVE ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_WARNING ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_TX_PASSIVE ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_TX_WARNING ; 
 int CAN_ERR_PROT ; 
 int /*<<< orphan*/  CAN_ERR_PROT_BIT ; 
 int /*<<< orphan*/  CAN_ERR_PROT_FORM ; 
 int /*<<< orphan*/  CAN_ERR_PROT_LOC_ACK ; 
 int /*<<< orphan*/  CAN_ERR_PROT_LOC_CRC_SEQ ; 
 int /*<<< orphan*/  CAN_ERR_PROT_STUFF ; 
 int /*<<< orphan*/  CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_PASSIVE ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_WARNING ; 
 int ENOMEM ; 
 int HECC_BUS_ERROR ; 
 int /*<<< orphan*/  HECC_CANES ; 
 int HECC_CANES_ACKE ; 
 int HECC_CANES_BE ; 
 int HECC_CANES_BO ; 
 int HECC_CANES_CRCE ; 
 int HECC_CANES_EP ; 
 int HECC_CANES_EW ; 
 int HECC_CANES_FE ; 
 int HECC_CANES_SE ; 
 int HECC_CANGIF_BOIF ; 
 int HECC_CANGIF_EPIF ; 
 int HECC_CANGIF_WLIF ; 
 int /*<<< orphan*/  HECC_CANGIM ; 
 int /*<<< orphan*/  HECC_CANMC ; 
 int /*<<< orphan*/  HECC_CANMC_CCR ; 
 int /*<<< orphan*/  HECC_CANREC ; 
 int /*<<< orphan*/  HECC_CANTEC ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  hecc_clear_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hecc_read (struct ti_hecc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hecc_set_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static int ti_hecc_error(struct net_device *ndev, int int_status,
	int err_status)
{
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;

	/* propagate the error condition to the can stack */
	skb = alloc_can_err_skb(ndev, &cf);
	if (!skb) {
		if (printk_ratelimit())
			netdev_err(priv->ndev,
				"ti_hecc_error: alloc_can_err_skb() failed\n");
		return -ENOMEM;
	}

	if (int_status & HECC_CANGIF_WLIF) { /* warning level int */
		if ((int_status & HECC_CANGIF_BOIF) == 0) {
			priv->can.state = CAN_STATE_ERROR_WARNING;
			++priv->can.can_stats.error_warning;
			cf->can_id |= CAN_ERR_CRTL;
			if (hecc_read(priv, HECC_CANTEC) > 96)
				cf->data[1] |= CAN_ERR_CRTL_TX_WARNING;
			if (hecc_read(priv, HECC_CANREC) > 96)
				cf->data[1] |= CAN_ERR_CRTL_RX_WARNING;
		}
		hecc_set_bit(priv, HECC_CANES, HECC_CANES_EW);
		netdev_dbg(priv->ndev, "Error Warning interrupt\n");
		hecc_clear_bit(priv, HECC_CANMC, HECC_CANMC_CCR);
	}

	if (int_status & HECC_CANGIF_EPIF) { /* error passive int */
		if ((int_status & HECC_CANGIF_BOIF) == 0) {
			priv->can.state = CAN_STATE_ERROR_PASSIVE;
			++priv->can.can_stats.error_passive;
			cf->can_id |= CAN_ERR_CRTL;
			if (hecc_read(priv, HECC_CANTEC) > 127)
				cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
			if (hecc_read(priv, HECC_CANREC) > 127)
				cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		}
		hecc_set_bit(priv, HECC_CANES, HECC_CANES_EP);
		netdev_dbg(priv->ndev, "Error passive interrupt\n");
		hecc_clear_bit(priv, HECC_CANMC, HECC_CANMC_CCR);
	}

	/*
	 * Need to check busoff condition in error status register too to
	 * ensure warning interrupts don't hog the system
	 */
	if ((int_status & HECC_CANGIF_BOIF) || (err_status & HECC_CANES_BO)) {
		priv->can.state = CAN_STATE_BUS_OFF;
		cf->can_id |= CAN_ERR_BUSOFF;
		hecc_set_bit(priv, HECC_CANES, HECC_CANES_BO);
		hecc_clear_bit(priv, HECC_CANMC, HECC_CANMC_CCR);
		/* Disable all interrupts in bus-off to avoid int hog */
		hecc_write(priv, HECC_CANGIM, 0);
		++priv->can.can_stats.bus_off;
		can_bus_off(ndev);
	}

	if (err_status & HECC_BUS_ERROR) {
		++priv->can.can_stats.bus_error;
		cf->can_id |= CAN_ERR_BUSERROR | CAN_ERR_PROT;
		if (err_status & HECC_CANES_FE) {
			hecc_set_bit(priv, HECC_CANES, HECC_CANES_FE);
			cf->data[2] |= CAN_ERR_PROT_FORM;
		}
		if (err_status & HECC_CANES_BE) {
			hecc_set_bit(priv, HECC_CANES, HECC_CANES_BE);
			cf->data[2] |= CAN_ERR_PROT_BIT;
		}
		if (err_status & HECC_CANES_SE) {
			hecc_set_bit(priv, HECC_CANES, HECC_CANES_SE);
			cf->data[2] |= CAN_ERR_PROT_STUFF;
		}
		if (err_status & HECC_CANES_CRCE) {
			hecc_set_bit(priv, HECC_CANES, HECC_CANES_CRCE);
			cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		}
		if (err_status & HECC_CANES_ACKE) {
			hecc_set_bit(priv, HECC_CANES, HECC_CANES_ACKE);
			cf->data[3] = CAN_ERR_PROT_LOC_ACK;
		}
	}

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_rx(skb);

	return 0;
}