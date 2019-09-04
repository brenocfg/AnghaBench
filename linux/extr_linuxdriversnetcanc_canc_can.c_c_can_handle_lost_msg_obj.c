#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int /*<<< orphan*/ * data; int /*<<< orphan*/  can_id; } ;
struct c_can_priv {int /*<<< orphan*/  (* write_reg ) (struct c_can_priv*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_OVERFLOW ; 
 int /*<<< orphan*/  C_CAN_IFACE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IF_COMM_CONTROL ; 
 int IF_MCONT_INTPND ; 
 int IF_MCONT_MSGLST ; 
 int IF_MCONT_NEWDAT ; 
 int /*<<< orphan*/  MSGCTRL_REG ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  c_can_object_put (struct net_device*,int,int,int /*<<< orphan*/ ) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int c_can_handle_lost_msg_obj(struct net_device *dev,
				     int iface, int objno, u32 ctrl)
{
	struct net_device_stats *stats = &dev->stats;
	struct c_can_priv *priv = netdev_priv(dev);
	struct can_frame *frame;
	struct sk_buff *skb;

	ctrl &= ~(IF_MCONT_MSGLST | IF_MCONT_INTPND | IF_MCONT_NEWDAT);
	priv->write_reg(priv, C_CAN_IFACE(MSGCTRL_REG, iface), ctrl);
	c_can_object_put(dev, iface, objno, IF_COMM_CONTROL);

	stats->rx_errors++;
	stats->rx_over_errors++;

	/* create an error msg */
	skb = alloc_can_err_skb(dev, &frame);
	if (unlikely(!skb))
		return 0;

	frame->can_id |= CAN_ERR_CRTL;
	frame->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	netif_receive_skb(skb);
	return 1;
}