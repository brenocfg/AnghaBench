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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct netsec_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netsec_unregister_mdio (struct netsec_priv*) ; 
 struct netsec_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netsec_remove(struct platform_device *pdev)
{
	struct netsec_priv *priv = platform_get_drvdata(pdev);

	unregister_netdev(priv->ndev);

	netsec_unregister_mdio(priv);

	netif_napi_del(&priv->napi);

	pm_runtime_disable(&pdev->dev);
	free_netdev(priv->ndev);

	return 0;
}