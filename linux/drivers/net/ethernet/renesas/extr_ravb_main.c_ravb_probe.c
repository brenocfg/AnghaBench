#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {scalar_t__ start; } ;
struct ravb_private {int emac_irq; int* rx_irqs; int* tx_irqs; int chip_id; int desc_bat_size; int /*<<< orphan*/  desc_bat_dma; TYPE_7__* desc_bat; int /*<<< orphan*/ * napi; int /*<<< orphan*/  msg_enable; int /*<<< orphan*/  ts_skb_list; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  clk; void* avb_link_active_low; void* no_avb_link; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  addr; int /*<<< orphan*/ * num_rx_ring; int /*<<< orphan*/ * num_tx_ring; struct platform_device* pdev; struct net_device* ndev; } ;
struct ravb_desc {int dummy; } ;
struct TYPE_16__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  parent; } ;
struct net_device {int irq; TYPE_1__ dev; int /*<<< orphan*/  dev_addr; scalar_t__ base_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  min_mtu; scalar_t__ max_mtu; void* hw_features; void* features; } ;
struct device_node {int dummy; } ;
typedef  enum ravb_chip_id { ____Placeholder_ravb_chip_id } ravb_chip_id ;
struct TYPE_17__ {int /*<<< orphan*/  die_dt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_RX_RING_SIZE ; 
 int /*<<< orphan*/  BE_TX_RING_SIZE ; 
 int /*<<< orphan*/  DBAT ; 
 int DBAT_ENTRY_NUM ; 
 int /*<<< orphan*/  DT_EOS ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  GCCR ; 
 int /*<<< orphan*/  GCCR_LTI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NC_RX_RING_SIZE ; 
 int /*<<< orphan*/  NC_TX_RING_SIZE ; 
 void* NETIF_F_RXCSUM ; 
 int NUM_RX_QUEUE ; 
 int /*<<< orphan*/  NUM_TX_DESC_GEN2 ; 
 int /*<<< orphan*/  NUM_TX_DESC_GEN3 ; 
 int NUM_TX_QUEUE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t RAVB_BE ; 
 int /*<<< orphan*/  RAVB_DEF_MSG_ENABLE ; 
 size_t RAVB_NC ; 
 int RCAR_GEN2 ; 
 int RCAR_GEN3 ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_2__*) ; 
 scalar_t__ VLAN_HLEN ; 
 struct net_device* alloc_etherdev_mqs (int,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_2__*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 TYPE_7__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_2__*) ; 
 int /*<<< orphan*/  of_get_mac_address (struct device_node*) ; 
 int /*<<< orphan*/  of_get_phy_mode (struct device_node*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  ravb_ethtool_ops ; 
 int ravb_mdio_init (struct ravb_private*) ; 
 int /*<<< orphan*/  ravb_mdio_release (struct ravb_private*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_netdev_ops ; 
 int /*<<< orphan*/  ravb_poll ; 
 int /*<<< orphan*/  ravb_ptp_init (struct net_device*,struct platform_device*) ; 
 int /*<<< orphan*/  ravb_ptp_stop (struct net_device*) ; 
 int /*<<< orphan*/  ravb_read_mac_address (struct net_device*,int /*<<< orphan*/ ) ; 
 char** ravb_rx_irqs ; 
 int /*<<< orphan*/  ravb_set_config_mode (struct net_device*) ; 
 int /*<<< orphan*/  ravb_set_delay_mode (struct net_device*) ; 
 int ravb_set_gti (struct net_device*) ; 
 char** ravb_tx_irqs ; 
 int /*<<< orphan*/  ravb_tx_timeout_work ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ravb_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct ravb_private *priv;
	enum ravb_chip_id chip_id;
	struct net_device *ndev;
	int error, irq, q;
	struct resource *res;
	int i;

	if (!np) {
		dev_err(&pdev->dev,
			"this driver is required to be instantiated from device tree\n");
		return -EINVAL;
	}

	/* Get base address */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "invalid resource\n");
		return -EINVAL;
	}

	ndev = alloc_etherdev_mqs(sizeof(struct ravb_private),
				  NUM_TX_QUEUE, NUM_RX_QUEUE);
	if (!ndev)
		return -ENOMEM;

	ndev->features = NETIF_F_RXCSUM;
	ndev->hw_features = NETIF_F_RXCSUM;

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	/* The Ether-specific entries in the device structure. */
	ndev->base_addr = res->start;

	chip_id = (enum ravb_chip_id)of_device_get_match_data(&pdev->dev);

	if (chip_id == RCAR_GEN3)
		irq = platform_get_irq_byname(pdev, "ch22");
	else
		irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		error = irq;
		goto out_release;
	}
	ndev->irq = irq;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->pdev = pdev;
	priv->num_tx_ring[RAVB_BE] = BE_TX_RING_SIZE;
	priv->num_rx_ring[RAVB_BE] = BE_RX_RING_SIZE;
	priv->num_tx_ring[RAVB_NC] = NC_TX_RING_SIZE;
	priv->num_rx_ring[RAVB_NC] = NC_RX_RING_SIZE;
	priv->addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->addr)) {
		error = PTR_ERR(priv->addr);
		goto out_release;
	}

	spin_lock_init(&priv->lock);
	INIT_WORK(&priv->work, ravb_tx_timeout_work);

	priv->phy_interface = of_get_phy_mode(np);

	priv->no_avb_link = of_property_read_bool(np, "renesas,no-ether-link");
	priv->avb_link_active_low =
		of_property_read_bool(np, "renesas,ether-link-active-low");

	if (chip_id == RCAR_GEN3) {
		irq = platform_get_irq_byname(pdev, "ch24");
		if (irq < 0) {
			error = irq;
			goto out_release;
		}
		priv->emac_irq = irq;
		for (i = 0; i < NUM_RX_QUEUE; i++) {
			irq = platform_get_irq_byname(pdev, ravb_rx_irqs[i]);
			if (irq < 0) {
				error = irq;
				goto out_release;
			}
			priv->rx_irqs[i] = irq;
		}
		for (i = 0; i < NUM_TX_QUEUE; i++) {
			irq = platform_get_irq_byname(pdev, ravb_tx_irqs[i]);
			if (irq < 0) {
				error = irq;
				goto out_release;
			}
			priv->tx_irqs[i] = irq;
		}
	}

	priv->chip_id = chip_id;

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk)) {
		error = PTR_ERR(priv->clk);
		goto out_release;
	}

	ndev->max_mtu = 2048 - (ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN);
	ndev->min_mtu = ETH_MIN_MTU;

	priv->num_tx_desc = chip_id == RCAR_GEN2 ?
		NUM_TX_DESC_GEN2 : NUM_TX_DESC_GEN3;

	/* Set function */
	ndev->netdev_ops = &ravb_netdev_ops;
	ndev->ethtool_ops = &ravb_ethtool_ops;

	/* Set AVB config mode */
	ravb_set_config_mode(ndev);

	/* Set GTI value */
	error = ravb_set_gti(ndev);
	if (error)
		goto out_release;

	/* Request GTI loading */
	ravb_modify(ndev, GCCR, GCCR_LTI, GCCR_LTI);

	if (priv->chip_id != RCAR_GEN2)
		ravb_set_delay_mode(ndev);

	/* Allocate descriptor base address table */
	priv->desc_bat_size = sizeof(struct ravb_desc) * DBAT_ENTRY_NUM;
	priv->desc_bat = dma_alloc_coherent(ndev->dev.parent, priv->desc_bat_size,
					    &priv->desc_bat_dma, GFP_KERNEL);
	if (!priv->desc_bat) {
		dev_err(&pdev->dev,
			"Cannot allocate desc base address table (size %d bytes)\n",
			priv->desc_bat_size);
		error = -ENOMEM;
		goto out_release;
	}
	for (q = RAVB_BE; q < DBAT_ENTRY_NUM; q++)
		priv->desc_bat[q].die_dt = DT_EOS;
	ravb_write(ndev, priv->desc_bat_dma, DBAT);

	/* Initialise HW timestamp list */
	INIT_LIST_HEAD(&priv->ts_skb_list);

	/* Initialise PTP Clock driver */
	if (chip_id != RCAR_GEN2)
		ravb_ptp_init(ndev, pdev);

	/* Debug message level */
	priv->msg_enable = RAVB_DEF_MSG_ENABLE;

	/* Read and set MAC address */
	ravb_read_mac_address(ndev, of_get_mac_address(np));
	if (!is_valid_ether_addr(ndev->dev_addr)) {
		dev_warn(&pdev->dev,
			 "no valid MAC address supplied, using a random one\n");
		eth_hw_addr_random(ndev);
	}

	/* MDIO bus init */
	error = ravb_mdio_init(priv);
	if (error) {
		dev_err(&pdev->dev, "failed to initialize MDIO\n");
		goto out_dma_free;
	}

	netif_napi_add(ndev, &priv->napi[RAVB_BE], ravb_poll, 64);
	netif_napi_add(ndev, &priv->napi[RAVB_NC], ravb_poll, 64);

	/* Network device register */
	error = register_netdev(ndev);
	if (error)
		goto out_napi_del;

	device_set_wakeup_capable(&pdev->dev, 1);

	/* Print device information */
	netdev_info(ndev, "Base address at %#x, %pM, IRQ %d.\n",
		    (u32)ndev->base_addr, ndev->dev_addr, ndev->irq);

	platform_set_drvdata(pdev, ndev);

	return 0;

out_napi_del:
	netif_napi_del(&priv->napi[RAVB_NC]);
	netif_napi_del(&priv->napi[RAVB_BE]);
	ravb_mdio_release(priv);
out_dma_free:
	dma_free_coherent(ndev->dev.parent, priv->desc_bat_size, priv->desc_bat,
			  priv->desc_bat_dma);

	/* Stop PTP Clock driver */
	if (chip_id != RCAR_GEN2)
		ravb_ptp_stop(ndev);
out_release:
	free_netdev(ndev);

	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	return error;
}