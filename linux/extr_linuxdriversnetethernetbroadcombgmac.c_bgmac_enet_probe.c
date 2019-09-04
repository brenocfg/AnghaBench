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
struct net_device {int features; int hw_features; int vlan_features; int /*<<< orphan*/  phydev; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  irq; } ;
struct bgmac {int feature_flags; int int_mask; int /*<<< orphan*/  dev; struct net_device* net_dev; int /*<<< orphan*/  napi; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_OOB_SEL_OUT_A30 ; 
 int BGMAC_FEAT_IDM_MASK ; 
 int BGMAC_FEAT_IRQ_ID_OOB_6 ; 
 int BGMAC_IS_ERRMASK ; 
 int BGMAC_IS_RX ; 
 int BGMAC_IS_TX_MASK ; 
 int /*<<< orphan*/  BGMAC_WEIGHT ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ bcm47xx_nvram_getenv (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgmac_chip_intrs_off (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_chip_reset (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_clk_enable (struct bgmac*,int /*<<< orphan*/ ) ; 
 int bgmac_dma_alloc (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_dma_free (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_idm_write (struct bgmac*,int /*<<< orphan*/ ,int) ; 
 int bgmac_phy_connect (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_poll ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct bgmac*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 

int bgmac_enet_probe(struct bgmac *bgmac)
{
	struct net_device *net_dev = bgmac->net_dev;
	int err;

	bgmac_chip_intrs_off(bgmac);

	net_dev->irq = bgmac->irq;
	SET_NETDEV_DEV(net_dev, bgmac->dev);
	dev_set_drvdata(bgmac->dev, bgmac);

	if (!is_valid_ether_addr(net_dev->dev_addr)) {
		dev_err(bgmac->dev, "Invalid MAC addr: %pM\n",
			net_dev->dev_addr);
		eth_hw_addr_random(net_dev);
		dev_warn(bgmac->dev, "Using random MAC: %pM\n",
			 net_dev->dev_addr);
	}

	/* This (reset &) enable is not preset in specs or reference driver but
	 * Broadcom does it in arch PCI code when enabling fake PCI device.
	 */
	bgmac_clk_enable(bgmac, 0);

	/* This seems to be fixing IRQ by assigning OOB #6 to the core */
	if (!(bgmac->feature_flags & BGMAC_FEAT_IDM_MASK)) {
		if (bgmac->feature_flags & BGMAC_FEAT_IRQ_ID_OOB_6)
			bgmac_idm_write(bgmac, BCMA_OOB_SEL_OUT_A30, 0x86);
	}

	bgmac_chip_reset(bgmac);

	err = bgmac_dma_alloc(bgmac);
	if (err) {
		dev_err(bgmac->dev, "Unable to alloc memory for DMA\n");
		goto err_out;
	}

	bgmac->int_mask = BGMAC_IS_ERRMASK | BGMAC_IS_RX | BGMAC_IS_TX_MASK;
	if (bcm47xx_nvram_getenv("et0_no_txint", NULL, 0) == 0)
		bgmac->int_mask &= ~BGMAC_IS_TX_MASK;

	netif_napi_add(net_dev, &bgmac->napi, bgmac_poll, BGMAC_WEIGHT);

	err = bgmac_phy_connect(bgmac);
	if (err) {
		dev_err(bgmac->dev, "Cannot connect to phy\n");
		goto err_dma_free;
	}

	net_dev->features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	net_dev->hw_features = net_dev->features;
	net_dev->vlan_features = net_dev->features;

	err = register_netdev(bgmac->net_dev);
	if (err) {
		dev_err(bgmac->dev, "Cannot register net device\n");
		goto err_phy_disconnect;
	}

	netif_carrier_off(net_dev);

	return 0;

err_phy_disconnect:
	phy_disconnect(net_dev->phydev);
err_dma_free:
	bgmac_dma_free(bgmac);
err_out:

	return err;
}