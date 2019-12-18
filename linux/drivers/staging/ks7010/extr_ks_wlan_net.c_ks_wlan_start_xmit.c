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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ks_wlan_private {scalar_t__ dev_state; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_READY ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int hostif_data_request (struct ks_wlan_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 

__attribute__((used)) static
int ks_wlan_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	int ret;

	netdev_dbg(dev, "in_interrupt()=%ld\n", in_interrupt());

	if (!skb) {
		netdev_err(dev, "ks_wlan:  skb == NULL!!!\n");
		return 0;
	}
	if (priv->dev_state < DEVICE_STATE_READY) {
		dev_kfree_skb(skb);
		return 0;	/* not finished initialize */
	}

	if (netif_running(dev))
		netif_stop_queue(dev);

	ret = hostif_data_request(priv, skb);
	netif_trans_update(dev);

	if (ret)
		netdev_err(dev, "hostif_data_request error: =%d\n", ret);

	return 0;
}