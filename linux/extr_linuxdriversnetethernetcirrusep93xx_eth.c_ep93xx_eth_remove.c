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
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ep93xx_priv {int /*<<< orphan*/ * res; int /*<<< orphan*/ * base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ep93xx_free_buffers (struct ep93xx_priv*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct ep93xx_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ep93xx_eth_remove(struct platform_device *pdev)
{
	struct net_device *dev;
	struct ep93xx_priv *ep;

	dev = platform_get_drvdata(pdev);
	if (dev == NULL)
		return 0;

	ep = netdev_priv(dev);

	/* @@@ Force down.  */
	unregister_netdev(dev);
	ep93xx_free_buffers(ep);

	if (ep->base_addr != NULL)
		iounmap(ep->base_addr);

	if (ep->res != NULL) {
		release_resource(ep->res);
		kfree(ep->res);
	}

	free_netdev(dev);

	return 0;
}