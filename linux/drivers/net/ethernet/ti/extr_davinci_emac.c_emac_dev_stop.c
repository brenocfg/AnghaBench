#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; int end; } ;
struct device {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; scalar_t__ phydev; struct device dev; } ;
struct emac_priv {TYPE_1__* pdev; int /*<<< orphan*/  ndev; int /*<<< orphan*/  dma; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_SOFTRESET ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  cpdma_ctlr_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_int_disable (struct emac_priv*) ; 
 int /*<<< orphan*/  emac_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_msg_drv (struct emac_priv*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 struct resource* platform_get_resource (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int emac_dev_stop(struct net_device *ndev)
{
	struct resource *res;
	int i = 0;
	int irq_num;
	struct emac_priv *priv = netdev_priv(ndev);
	struct device *emac_dev = &ndev->dev;

	/* inform the upper layers. */
	netif_stop_queue(ndev);
	napi_disable(&priv->napi);

	netif_carrier_off(ndev);
	emac_int_disable(priv);
	cpdma_ctlr_stop(priv->dma);
	emac_write(EMAC_SOFTRESET, 1);

	if (ndev->phydev)
		phy_disconnect(ndev->phydev);

	/* Free IRQ */
	while ((res = platform_get_resource(priv->pdev, IORESOURCE_IRQ, i))) {
		for (irq_num = res->start; irq_num <= res->end; irq_num++)
			free_irq(irq_num, priv->ndev);
		i++;
	}

	if (netif_msg_drv(priv))
		dev_notice(emac_dev, "DaVinci EMAC: %s stopped\n", ndev->name);

	pm_runtime_put(&priv->pdev->dev);
	return 0;
}