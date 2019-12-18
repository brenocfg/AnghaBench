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
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; } ;
struct mpc52xx_fec_priv {int /*<<< orphan*/  fec; int /*<<< orphan*/  tx_dmatsk; int /*<<< orphan*/  rx_dmatsk; int /*<<< orphan*/ * phy_node; } ;
struct mpc52xx_fec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcom_fec_rx_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_fec_tx_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int
mpc52xx_fec_remove(struct platform_device *op)
{
	struct net_device *ndev;
	struct mpc52xx_fec_priv *priv;

	ndev = platform_get_drvdata(op);
	priv = netdev_priv(ndev);

	unregister_netdev(ndev);

	of_node_put(priv->phy_node);
	priv->phy_node = NULL;

	irq_dispose_mapping(ndev->irq);

	bcom_fec_rx_release(priv->rx_dmatsk);
	bcom_fec_tx_release(priv->tx_dmatsk);

	iounmap(priv->fec);

	release_mem_region(ndev->base_addr, sizeof(struct mpc52xx_fec));

	free_netdev(ndev);

	return 0;
}