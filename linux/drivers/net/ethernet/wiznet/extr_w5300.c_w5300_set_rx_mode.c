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
struct w5300_priv {int promisc; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 struct w5300_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  w5300_hw_start (struct w5300_priv*) ; 

__attribute__((used)) static void w5300_set_rx_mode(struct net_device *ndev)
{
	struct w5300_priv *priv = netdev_priv(ndev);
	bool set_promisc = (ndev->flags & IFF_PROMISC) != 0;

	if (priv->promisc != set_promisc) {
		priv->promisc = set_promisc;
		w5300_hw_start(priv);
	}
}