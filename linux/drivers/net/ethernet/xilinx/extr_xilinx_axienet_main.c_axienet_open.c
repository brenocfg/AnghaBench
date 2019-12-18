#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct axienet_local {scalar_t__ tx_irq; scalar_t__ rx_irq; scalar_t__ eth_irq; TYPE_2__* dev; int /*<<< orphan*/  dma_err_tasklet; int /*<<< orphan*/  phylink; TYPE_1__* mii_bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  axienet_device_reset (struct net_device*) ; 
 int /*<<< orphan*/  axienet_dma_err_handler ; 
 int /*<<< orphan*/  axienet_eth_irq ; 
 int /*<<< orphan*/  axienet_mdio_disable (struct axienet_local*) ; 
 int axienet_mdio_enable (struct axienet_local*) ; 
 int /*<<< orphan*/  axienet_rx_irq ; 
 int /*<<< orphan*/  axienet_tx_irq ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 
 int phylink_of_phy_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_stop (int /*<<< orphan*/ ) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axienet_open(struct net_device *ndev)
{
	int ret;
	struct axienet_local *lp = netdev_priv(ndev);

	dev_dbg(&ndev->dev, "axienet_open()\n");

	/* Disable the MDIO interface till Axi Ethernet Reset is completed.
	 * When we do an Axi Ethernet reset, it resets the complete core
	 * including the MDIO. MDIO must be disabled before resetting
	 * and re-enabled afterwards.
	 * Hold MDIO bus lock to avoid MDIO accesses during the reset.
	 */
	mutex_lock(&lp->mii_bus->mdio_lock);
	axienet_mdio_disable(lp);
	axienet_device_reset(ndev);
	ret = axienet_mdio_enable(lp);
	mutex_unlock(&lp->mii_bus->mdio_lock);
	if (ret < 0)
		return ret;

	ret = phylink_of_phy_connect(lp->phylink, lp->dev->of_node, 0);
	if (ret) {
		dev_err(lp->dev, "phylink_of_phy_connect() failed: %d\n", ret);
		return ret;
	}

	phylink_start(lp->phylink);

	/* Enable tasklets for Axi DMA error handling */
	tasklet_init(&lp->dma_err_tasklet, axienet_dma_err_handler,
		     (unsigned long) lp);

	/* Enable interrupts for Axi DMA Tx */
	ret = request_irq(lp->tx_irq, axienet_tx_irq, IRQF_SHARED,
			  ndev->name, ndev);
	if (ret)
		goto err_tx_irq;
	/* Enable interrupts for Axi DMA Rx */
	ret = request_irq(lp->rx_irq, axienet_rx_irq, IRQF_SHARED,
			  ndev->name, ndev);
	if (ret)
		goto err_rx_irq;
	/* Enable interrupts for Axi Ethernet core (if defined) */
	if (lp->eth_irq > 0) {
		ret = request_irq(lp->eth_irq, axienet_eth_irq, IRQF_SHARED,
				  ndev->name, ndev);
		if (ret)
			goto err_eth_irq;
	}

	return 0;

err_eth_irq:
	free_irq(lp->rx_irq, ndev);
err_rx_irq:
	free_irq(lp->tx_irq, ndev);
err_tx_irq:
	phylink_stop(lp->phylink);
	phylink_disconnect_phy(lp->phylink);
	tasklet_kill(&lp->dma_err_tasklet);
	dev_err(lp->dev, "request_irq() failed\n");
	return ret;
}