#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virt_wifi_netdev_priv {TYPE_1__* upperdev; int /*<<< orphan*/  is_connected; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_handler_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  RX_HANDLER_ANOTHER ; 
 int /*<<< orphan*/  RX_HANDLER_CONSUMED ; 
 int /*<<< orphan*/  RX_HANDLER_PASS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct virt_wifi_netdev_priv* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rx_handler_result_t virt_wifi_rx_handler(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct virt_wifi_netdev_priv *priv =
		rcu_dereference(skb->dev->rx_handler_data);

	if (!priv->is_connected)
		return RX_HANDLER_PASS;

	/* GFP_ATOMIC because this is a packet interrupt handler. */
	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb) {
		dev_err(&priv->upperdev->dev, "can't skb_share_check\n");
		return RX_HANDLER_CONSUMED;
	}

	*pskb = skb;
	skb->dev = priv->upperdev;
	skb->pkt_type = PACKET_HOST;
	return RX_HANDLER_ANOTHER;
}