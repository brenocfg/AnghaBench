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
struct xlr_net_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX_FRIN_SPILL ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  send_to_rfr_fifo (struct xlr_net_priv*,void*) ; 
 void* xlr_alloc_skb () ; 

__attribute__((used)) static int xlr_net_fill_rx_ring(struct net_device *ndev)
{
	void *skb_data;
	struct xlr_net_priv *priv = netdev_priv(ndev);
	int i;

	for (i = 0; i < MAX_FRIN_SPILL / 4; i++) {
		skb_data = xlr_alloc_skb();
		if (!skb_data)
			return -ENOMEM;
		send_to_rfr_fifo(priv, skb_data);
	}
	netdev_info(ndev, "Rx ring setup done\n");
	return 0;
}