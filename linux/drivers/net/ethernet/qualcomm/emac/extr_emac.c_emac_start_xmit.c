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
struct emac_adapter {int /*<<< orphan*/  tx_q; } ;

/* Variables and functions */
 int emac_mac_tx_buf_send (struct emac_adapter*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int emac_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	return emac_mac_tx_buf_send(adpt, &adpt->tx_q, skb);
}