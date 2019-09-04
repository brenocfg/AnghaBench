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
struct xgmac_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  napi; int /*<<< orphan*/  pmt_irq; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct xgmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  xgmac_mac_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgmac_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct xgmac_priv *priv = netdev_priv(ndev);
	struct resource *res;

	xgmac_mac_disable(priv->base);

	/* Free the IRQ lines */
	free_irq(ndev->irq, ndev);
	free_irq(priv->pmt_irq, ndev);

	unregister_netdev(ndev);
	netif_napi_del(&priv->napi);

	iounmap(priv->base);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	free_netdev(ndev);

	return 0;
}