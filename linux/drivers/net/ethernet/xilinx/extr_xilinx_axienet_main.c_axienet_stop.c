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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct axienet_local {int options; scalar_t__ eth_irq; scalar_t__ tx_irq; scalar_t__ rx_irq; int /*<<< orphan*/  dma_err_tasklet; TYPE_1__* mii_bus; int /*<<< orphan*/  phylink; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XAE_IE_OFFSET ; 
 int XAE_OPTION_RXEN ; 
 int XAE_OPTION_TXEN ; 
 int XAXIDMA_CR_RUNSTOP_MASK ; 
 int XAXIDMA_IRQ_ALL_MASK ; 
 int /*<<< orphan*/  XAXIDMA_RX_CR_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_RX_SR_OFFSET ; 
 int XAXIDMA_SR_HALT_MASK ; 
 int /*<<< orphan*/  XAXIDMA_TX_CR_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_TX_SR_OFFSET ; 
 int /*<<< orphan*/  __axienet_device_reset (struct axienet_local*) ; 
 int /*<<< orphan*/  axienet_dma_bd_release (struct net_device*) ; 
 int axienet_dma_in32 (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_dma_out32 (struct axienet_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axienet_iow (struct axienet_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_mdio_disable (struct axienet_local*) ; 
 int /*<<< orphan*/  axienet_mdio_enable (struct axienet_local*) ; 
 int /*<<< orphan*/  axienet_setoptions (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axienet_stop(struct net_device *ndev)
{
	u32 cr, sr;
	int count;
	struct axienet_local *lp = netdev_priv(ndev);

	dev_dbg(&ndev->dev, "axienet_close()\n");

	phylink_stop(lp->phylink);
	phylink_disconnect_phy(lp->phylink);

	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));

	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	cr &= ~(XAXIDMA_CR_RUNSTOP_MASK | XAXIDMA_IRQ_ALL_MASK);
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET, cr);

	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	cr &= ~(XAXIDMA_CR_RUNSTOP_MASK | XAXIDMA_IRQ_ALL_MASK);
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, cr);

	axienet_iow(lp, XAE_IE_OFFSET, 0);

	/* Give DMAs a chance to halt gracefully */
	sr = axienet_dma_in32(lp, XAXIDMA_RX_SR_OFFSET);
	for (count = 0; !(sr & XAXIDMA_SR_HALT_MASK) && count < 5; ++count) {
		msleep(20);
		sr = axienet_dma_in32(lp, XAXIDMA_RX_SR_OFFSET);
	}

	sr = axienet_dma_in32(lp, XAXIDMA_TX_SR_OFFSET);
	for (count = 0; !(sr & XAXIDMA_SR_HALT_MASK) && count < 5; ++count) {
		msleep(20);
		sr = axienet_dma_in32(lp, XAXIDMA_TX_SR_OFFSET);
	}

	/* Do a reset to ensure DMA is really stopped */
	mutex_lock(&lp->mii_bus->mdio_lock);
	axienet_mdio_disable(lp);
	__axienet_device_reset(lp);
	axienet_mdio_enable(lp);
	mutex_unlock(&lp->mii_bus->mdio_lock);

	tasklet_kill(&lp->dma_err_tasklet);

	if (lp->eth_irq > 0)
		free_irq(lp->eth_irq, ndev);
	free_irq(lp->tx_irq, ndev);
	free_irq(lp->rx_irq, ndev);

	axienet_dma_bd_release(ndev);
	return 0;
}