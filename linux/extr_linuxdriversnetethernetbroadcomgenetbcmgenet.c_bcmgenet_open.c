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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct bcmgenet_priv {int crc_fwd_en; int /*<<< orphan*/  clk; scalar_t__ internal_phy; int /*<<< orphan*/  irq0; int /*<<< orphan*/  irq1; } ;

/* Variables and functions */
 int CMD_CRC_FWD ; 
 int EXT_ENERGY_DET_MASK ; 
 int /*<<< orphan*/  EXT_EXT_PWR_MGMT ; 
 int /*<<< orphan*/  GENET_POWER_PASSIVE ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  UMAC_CMD ; 
 unsigned long bcmgenet_dma_disable (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_dma_teardown (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_enable_dma (struct bcmgenet_priv*,unsigned long) ; 
 int bcmgenet_ext_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_ext_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_fini_dma (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_hfb_init (struct bcmgenet_priv*) ; 
 int bcmgenet_init_dma (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_isr0 ; 
 int /*<<< orphan*/  bcmgenet_isr1 ; 
 int bcmgenet_mii_probe (struct net_device*) ; 
 int /*<<< orphan*/  bcmgenet_netif_start (struct net_device*) ; 
 int /*<<< orphan*/  bcmgenet_power_down (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_power_up (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_set_hw_addr (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int bcmgenet_umac_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_umac_reset (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  init_umac (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct bcmgenet_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcmgenet_priv*) ; 

__attribute__((used)) static int bcmgenet_open(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	unsigned long dma_ctrl;
	u32 reg;
	int ret;

	netif_dbg(priv, ifup, dev, "bcmgenet_open\n");

	/* Turn on the clock */
	clk_prepare_enable(priv->clk);

	/* If this is an internal GPHY, power it back on now, before UniMAC is
	 * brought out of reset as absolutely no UniMAC activity is allowed
	 */
	if (priv->internal_phy)
		bcmgenet_power_up(priv, GENET_POWER_PASSIVE);

	/* take MAC out of reset */
	bcmgenet_umac_reset(priv);

	init_umac(priv);

	/* Make sure we reflect the value of CRC_CMD_FWD */
	reg = bcmgenet_umac_readl(priv, UMAC_CMD);
	priv->crc_fwd_en = !!(reg & CMD_CRC_FWD);

	bcmgenet_set_hw_addr(priv, dev->dev_addr);

	if (priv->internal_phy) {
		reg = bcmgenet_ext_readl(priv, EXT_EXT_PWR_MGMT);
		reg |= EXT_ENERGY_DET_MASK;
		bcmgenet_ext_writel(priv, reg, EXT_EXT_PWR_MGMT);
	}

	/* Disable RX/TX DMA and flush TX queues */
	dma_ctrl = bcmgenet_dma_disable(priv);

	/* Reinitialize TDMA and RDMA and SW housekeeping */
	ret = bcmgenet_init_dma(priv);
	if (ret) {
		netdev_err(dev, "failed to initialize DMA\n");
		goto err_clk_disable;
	}

	/* Always enable ring 16 - descriptor ring */
	bcmgenet_enable_dma(priv, dma_ctrl);

	/* HFB init */
	bcmgenet_hfb_init(priv);

	ret = request_irq(priv->irq0, bcmgenet_isr0, IRQF_SHARED,
			  dev->name, priv);
	if (ret < 0) {
		netdev_err(dev, "can't request IRQ %d\n", priv->irq0);
		goto err_fini_dma;
	}

	ret = request_irq(priv->irq1, bcmgenet_isr1, IRQF_SHARED,
			  dev->name, priv);
	if (ret < 0) {
		netdev_err(dev, "can't request IRQ %d\n", priv->irq1);
		goto err_irq0;
	}

	ret = bcmgenet_mii_probe(dev);
	if (ret) {
		netdev_err(dev, "failed to connect to PHY\n");
		goto err_irq1;
	}

	bcmgenet_netif_start(dev);

	netif_tx_start_all_queues(dev);

	return 0;

err_irq1:
	free_irq(priv->irq1, priv);
err_irq0:
	free_irq(priv->irq0, priv);
err_fini_dma:
	bcmgenet_dma_teardown(priv);
	bcmgenet_fini_dma(priv);
err_clk_disable:
	if (priv->internal_phy)
		bcmgenet_power_down(priv, GENET_POWER_PASSIVE);
	clk_disable_unprepare(priv->clk);
	return ret;
}