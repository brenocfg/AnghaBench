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
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct nb8800_priv {int /*<<< orphan*/  napi; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  phy_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NB8800_RXC_SR ; 
 int /*<<< orphan*/  NB8800_TXC_SR ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nb8800_dma_free (struct net_device*) ; 
 int nb8800_dma_init (struct net_device*) ; 
 int /*<<< orphan*/  nb8800_irq ; 
 int /*<<< orphan*/  nb8800_link_reconfigure ; 
 int /*<<< orphan*/  nb8800_mac_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  nb8800_mac_tx (struct net_device*,int) ; 
 int /*<<< orphan*/  nb8800_pause_adv (struct net_device*) ; 
 int /*<<< orphan*/  nb8800_start_rx (struct net_device*) ; 
 int /*<<< orphan*/  nb8800_writel (struct nb8800_priv*,int /*<<< orphan*/ ,int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int nb8800_open(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	struct phy_device *phydev;
	int err;

	/* clear any pending interrupts */
	nb8800_writel(priv, NB8800_RXC_SR, 0xf);
	nb8800_writel(priv, NB8800_TXC_SR, 0xf);

	err = nb8800_dma_init(dev);
	if (err)
		return err;

	err = request_irq(dev->irq, nb8800_irq, 0, dev_name(&dev->dev), dev);
	if (err)
		goto err_free_dma;

	nb8800_mac_rx(dev, true);
	nb8800_mac_tx(dev, true);

	phydev = of_phy_connect(dev, priv->phy_node,
				nb8800_link_reconfigure, 0,
				priv->phy_mode);
	if (!phydev) {
		err = -ENODEV;
		goto err_free_irq;
	}

	nb8800_pause_adv(dev);

	netdev_reset_queue(dev);
	napi_enable(&priv->napi);
	netif_start_queue(dev);

	nb8800_start_rx(dev);
	phy_start(phydev);

	return 0;

err_free_irq:
	free_irq(dev->irq, dev);
err_free_dma:
	nb8800_dma_free(dev);

	return err;
}