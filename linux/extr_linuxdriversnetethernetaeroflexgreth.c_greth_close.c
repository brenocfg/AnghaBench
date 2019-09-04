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
struct greth_private {int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  greth_clean_rings (struct greth_private*) ; 
 int /*<<< orphan*/  greth_disable_irqs (struct greth_private*) ; 
 int /*<<< orphan*/  greth_disable_rx (struct greth_private*) ; 
 int /*<<< orphan*/  greth_disable_tx (struct greth_private*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int greth_close(struct net_device *dev)
{
	struct greth_private *greth = netdev_priv(dev);

	napi_disable(&greth->napi);

	greth_disable_irqs(greth);
	greth_disable_tx(greth);
	greth_disable_rx(greth);

	netif_stop_queue(dev);

	free_irq(greth->irq, (void *) dev);

	greth_clean_rings(greth);

	return 0;
}