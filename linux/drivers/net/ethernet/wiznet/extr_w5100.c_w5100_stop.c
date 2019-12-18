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
struct w5100_priv {int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct w5100_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  w5100_hw_close (struct w5100_priv*) ; 

__attribute__((used)) static int w5100_stop(struct net_device *ndev)
{
	struct w5100_priv *priv = netdev_priv(ndev);

	netif_info(priv, ifdown, ndev, "shutting down\n");
	w5100_hw_close(priv);
	netif_carrier_off(ndev);
	netif_stop_queue(ndev);
	napi_disable(&priv->napi);
	return 0;
}