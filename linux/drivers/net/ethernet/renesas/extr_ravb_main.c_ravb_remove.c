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
struct ravb_private {scalar_t__ chip_id; int /*<<< orphan*/ * napi; int /*<<< orphan*/  desc_bat_dma; int /*<<< orphan*/  desc_bat; int /*<<< orphan*/  desc_bat_size; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCC ; 
 int /*<<< orphan*/  CCC_OPC_RESET ; 
 size_t RAVB_BE ; 
 size_t RAVB_NC ; 
 scalar_t__ RCAR_GEN2 ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ravb_mdio_release (struct ravb_private*) ; 
 int /*<<< orphan*/  ravb_ptp_stop (struct net_device*) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ravb_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct ravb_private *priv = netdev_priv(ndev);

	/* Stop PTP Clock driver */
	if (priv->chip_id != RCAR_GEN2)
		ravb_ptp_stop(ndev);

	dma_free_coherent(ndev->dev.parent, priv->desc_bat_size, priv->desc_bat,
			  priv->desc_bat_dma);
	/* Set reset mode */
	ravb_write(ndev, CCC_OPC_RESET, CCC);
	pm_runtime_put_sync(&pdev->dev);
	unregister_netdev(ndev);
	netif_napi_del(&priv->napi[RAVB_NC]);
	netif_napi_del(&priv->napi[RAVB_BE]);
	ravb_mdio_release(priv);
	pm_runtime_disable(&pdev->dev);
	free_netdev(ndev);
	platform_set_drvdata(pdev, NULL);

	return 0;
}