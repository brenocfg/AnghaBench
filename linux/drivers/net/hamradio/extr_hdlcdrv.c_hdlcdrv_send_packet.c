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
struct sk_buff {scalar_t__ protocol; scalar_t__* data; int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct hdlcdrv_state {struct sk_buff* skb; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  ax25_ip_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  do_kiss_params (struct hdlcdrv_state*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct hdlcdrv_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t hdlcdrv_send_packet(struct sk_buff *skb,
				       struct net_device *dev)
{
	struct hdlcdrv_state *sm = netdev_priv(dev);

	if (skb->protocol == htons(ETH_P_IP))
		return ax25_ip_xmit(skb);

	if (skb->data[0] != 0) {
		do_kiss_params(sm, skb->data, skb->len);
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	if (sm->skb) {
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	netif_stop_queue(dev);
	sm->skb = skb;
	return NETDEV_TX_OK;
}