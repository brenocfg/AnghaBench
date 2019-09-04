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
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  error_warning; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  bus_off; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; TYPE_1__ can_stats; } ;
struct cc770_priv {int control_normal_mode; TYPE_2__ can; } ;
struct can_frame {int* data; scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_ACK ; 
 int /*<<< orphan*/  CAN_ERR_BUSOFF ; 
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int CAN_ERR_CRTL_RX_PASSIVE ; 
 int CAN_ERR_CRTL_RX_WARNING ; 
 int CAN_ERR_CRTL_TX_PASSIVE ; 
 int CAN_ERR_CRTL_TX_WARNING ; 
 int /*<<< orphan*/  CAN_ERR_PROT ; 
 int CAN_ERR_PROT_ACTIVE ; 
 int CAN_ERR_PROT_BIT0 ; 
 int CAN_ERR_PROT_BIT1 ; 
 int CAN_ERR_PROT_FORM ; 
 int CAN_ERR_PROT_LOC_CRC_SEQ ; 
 int CAN_ERR_PROT_STUFF ; 
 int /*<<< orphan*/  CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_PASSIVE ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_WARNING ; 
 int CTRL_EAF ; 
 int /*<<< orphan*/  CTRL_INI ; 
 int ENOMEM ; 
 int STAT_BOFF ; 
 int STAT_LEC_ACK ; 
#define  STAT_LEC_BIT0 132 
#define  STAT_LEC_BIT1 131 
#define  STAT_LEC_CRC 130 
#define  STAT_LEC_FORM 129 
 int STAT_LEC_MASK ; 
#define  STAT_LEC_STUFF 128 
 int STAT_WARN ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 void* cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rx_error_counter ; 
 int /*<<< orphan*/  tx_error_counter ; 

__attribute__((used)) static int cc770_err(struct net_device *dev, u8 status)
{
	struct cc770_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	u8 lec;

	netdev_dbg(dev, "status interrupt (%#x)\n", status);

	skb = alloc_can_err_skb(dev, &cf);
	if (!skb)
		return -ENOMEM;

	/* Use extended functions of the CC770 */
	if (priv->control_normal_mode & CTRL_EAF) {
		cf->data[6] = cc770_read_reg(priv, tx_error_counter);
		cf->data[7] = cc770_read_reg(priv, rx_error_counter);
	}

	if (status & STAT_BOFF) {
		/* Disable interrupts */
		cc770_write_reg(priv, control, CTRL_INI);
		cf->can_id |= CAN_ERR_BUSOFF;
		priv->can.state = CAN_STATE_BUS_OFF;
		priv->can.can_stats.bus_off++;
		can_bus_off(dev);
	} else if (status & STAT_WARN) {
		cf->can_id |= CAN_ERR_CRTL;
		/* Only the CC770 does show error passive */
		if (cf->data[7] > 127) {
			cf->data[1] = CAN_ERR_CRTL_RX_PASSIVE |
				CAN_ERR_CRTL_TX_PASSIVE;
			priv->can.state = CAN_STATE_ERROR_PASSIVE;
			priv->can.can_stats.error_passive++;
		} else {
			cf->data[1] = CAN_ERR_CRTL_RX_WARNING |
				CAN_ERR_CRTL_TX_WARNING;
			priv->can.state = CAN_STATE_ERROR_WARNING;
			priv->can.can_stats.error_warning++;
		}
	} else {
		/* Back to error avtive */
		cf->can_id |= CAN_ERR_PROT;
		cf->data[2] = CAN_ERR_PROT_ACTIVE;
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
	}

	lec = status & STAT_LEC_MASK;
	if (lec < 7 && lec > 0) {
		if (lec == STAT_LEC_ACK) {
			cf->can_id |= CAN_ERR_ACK;
		} else {
			cf->can_id |= CAN_ERR_PROT;
			switch (lec) {
			case STAT_LEC_STUFF:
				cf->data[2] |= CAN_ERR_PROT_STUFF;
				break;
			case STAT_LEC_FORM:
				cf->data[2] |= CAN_ERR_PROT_FORM;
				break;
			case STAT_LEC_BIT1:
				cf->data[2] |= CAN_ERR_PROT_BIT1;
				break;
			case STAT_LEC_BIT0:
				cf->data[2] |= CAN_ERR_PROT_BIT0;
				break;
			case STAT_LEC_CRC:
				cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
				break;
			}
		}
	}


	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_rx(skb);

	return 0;
}