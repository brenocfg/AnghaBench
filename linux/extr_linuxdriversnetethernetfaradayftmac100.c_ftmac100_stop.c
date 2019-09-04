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
struct net_device {int dummy; } ;
struct ftmac100 {int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ftmac100_disable_all_int (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_free_buffers (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_stop_hw (struct ftmac100*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct ftmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int ftmac100_stop(struct net_device *netdev)
{
	struct ftmac100 *priv = netdev_priv(netdev);

	ftmac100_disable_all_int(priv);
	netif_stop_queue(netdev);
	napi_disable(&priv->napi);
	ftmac100_stop_hw(priv);
	free_irq(priv->irq, netdev);
	ftmac100_free_buffers(priv);

	return 0;
}