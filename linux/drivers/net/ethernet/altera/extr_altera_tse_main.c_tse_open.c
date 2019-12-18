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
struct net_device {int dev_addr; scalar_t__ phydev; int /*<<< orphan*/  name; } ;
struct altera_tse_private {int revision; int rx_ring_size; int rx_irq; int tx_irq; int /*<<< orphan*/  mac_cfg_lock; TYPE_1__* dmaops; int /*<<< orphan*/  napi; int /*<<< orphan*/  rxdma_irq_lock; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  tx_ring_size; } ;
struct TYPE_2__ {int (* init_dma ) (struct altera_tse_private*) ;int /*<<< orphan*/  (* start_rxdma ) (struct altera_tse_private*) ;int /*<<< orphan*/  (* add_rx_desc ) (struct altera_tse_private*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* enable_txirq ) (struct altera_tse_private*) ;int /*<<< orphan*/  (* enable_rxirq ) (struct altera_tse_private*) ;int /*<<< orphan*/  (* reset_dma ) (struct altera_tse_private*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int alloc_init_skbufs (struct altera_tse_private*) ; 
 int /*<<< orphan*/  altera_isr ; 
 int dma_rx_num ; 
 int /*<<< orphan*/  dma_tx_num ; 
 int /*<<< orphan*/  free_irq (int,struct net_device*) ; 
 int /*<<< orphan*/  free_skbufs (struct net_device*) ; 
 int init_mac (struct altera_tse_private*) ; 
 int init_sgmii_pcs (struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 scalar_t__ netif_msg_ifup (struct altera_tse_private*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (scalar_t__) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int reset_mac (struct altera_tse_private*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  stub2 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  stub3 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  stub4 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  stub5 (struct altera_tse_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  tse_set_mac (struct altera_tse_private*,int) ; 

__attribute__((used)) static int tse_open(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	int ret = 0;
	int i;
	unsigned long int flags;

	/* Reset and configure TSE MAC and probe associated PHY */
	ret = priv->dmaops->init_dma(priv);
	if (ret != 0) {
		netdev_err(dev, "Cannot initialize DMA\n");
		goto phy_error;
	}

	if (netif_msg_ifup(priv))
		netdev_warn(dev, "device MAC address %pM\n",
			    dev->dev_addr);

	if ((priv->revision < 0xd00) || (priv->revision > 0xe00))
		netdev_warn(dev, "TSE revision %x\n", priv->revision);

	spin_lock(&priv->mac_cfg_lock);
	/* no-op if MAC not operating in SGMII mode*/
	ret = init_sgmii_pcs(dev);
	if (ret) {
		netdev_err(dev,
			   "Cannot init the SGMII PCS (error: %d)\n", ret);
		spin_unlock(&priv->mac_cfg_lock);
		goto phy_error;
	}

	ret = reset_mac(priv);
	/* Note that reset_mac will fail if the clocks are gated by the PHY
	 * due to the PHY being put into isolation or power down mode.
	 * This is not an error if reset fails due to no clock.
	 */
	if (ret)
		netdev_dbg(dev, "Cannot reset MAC core (error: %d)\n", ret);

	ret = init_mac(priv);
	spin_unlock(&priv->mac_cfg_lock);
	if (ret) {
		netdev_err(dev, "Cannot init MAC core (error: %d)\n", ret);
		goto alloc_skbuf_error;
	}

	priv->dmaops->reset_dma(priv);

	/* Create and initialize the TX/RX descriptors chains. */
	priv->rx_ring_size = dma_rx_num;
	priv->tx_ring_size = dma_tx_num;
	ret = alloc_init_skbufs(priv);
	if (ret) {
		netdev_err(dev, "DMA descriptors initialization failed\n");
		goto alloc_skbuf_error;
	}


	/* Register RX interrupt */
	ret = request_irq(priv->rx_irq, altera_isr, IRQF_SHARED,
			  dev->name, dev);
	if (ret) {
		netdev_err(dev, "Unable to register RX interrupt %d\n",
			   priv->rx_irq);
		goto init_error;
	}

	/* Register TX interrupt */
	ret = request_irq(priv->tx_irq, altera_isr, IRQF_SHARED,
			  dev->name, dev);
	if (ret) {
		netdev_err(dev, "Unable to register TX interrupt %d\n",
			   priv->tx_irq);
		goto tx_request_irq_error;
	}

	/* Enable DMA interrupts */
	spin_lock_irqsave(&priv->rxdma_irq_lock, flags);
	priv->dmaops->enable_rxirq(priv);
	priv->dmaops->enable_txirq(priv);

	/* Setup RX descriptor chain */
	for (i = 0; i < priv->rx_ring_size; i++)
		priv->dmaops->add_rx_desc(priv, &priv->rx_ring[i]);

	spin_unlock_irqrestore(&priv->rxdma_irq_lock, flags);

	if (dev->phydev)
		phy_start(dev->phydev);

	napi_enable(&priv->napi);
	netif_start_queue(dev);

	priv->dmaops->start_rxdma(priv);

	/* Start MAC Rx/Tx */
	spin_lock(&priv->mac_cfg_lock);
	tse_set_mac(priv, true);
	spin_unlock(&priv->mac_cfg_lock);

	return 0;

tx_request_irq_error:
	free_irq(priv->rx_irq, dev);
init_error:
	free_skbufs(dev);
alloc_skbuf_error:
phy_error:
	return ret;
}