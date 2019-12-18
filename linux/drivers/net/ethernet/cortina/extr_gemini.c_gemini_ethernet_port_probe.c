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
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device* parent; } ;
struct platform_device {struct device dev; } ;
struct net_device {unsigned int dev_id; int irq; int hw_features; int features; int /*<<< orphan*/  dev_addr; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct gemini_ethernet_port {unsigned int id; int irq; struct net_device* netdev; struct device* dev; int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  napi; scalar_t__ freeq_refill; int /*<<< orphan*/  config_lock; void* reset; void* pclk; void* gmac_base; void* dma_base; int /*<<< orphan*/  msg_enable; struct gemini_ethernet* geth; } ;
struct gemini_ethernet {struct gemini_ethernet_port* port1; struct gemini_ethernet_port* port0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MSG_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_NAPI_WEIGHT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int GMAC_OFFLOAD_FEATURES ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int NETIF_F_GRO ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  TX_QUEUE_NUM ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct gemini_ethernet* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gemini_ethernet_port*) ; 
 void* devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  gemini_ethernet_init (struct gemini_ethernet*) ; 
 int /*<<< orphan*/  gemini_port_irq ; 
 int /*<<< orphan*/  gemini_port_irq_thread ; 
 int /*<<< orphan*/  gemini_port_save_mac_addr (struct gemini_ethernet_port*) ; 
 int /*<<< orphan*/  gmac_351x_ethtool_ops ; 
 int /*<<< orphan*/  gmac_351x_ops ; 
 int /*<<< orphan*/  gmac_clear_hw_stats (struct net_device*) ; 
 int /*<<< orphan*/  gmac_napi_poll ; 
 int gmac_setup_phy (struct net_device*) ; 
 int /*<<< orphan*/  gmac_write_mac_address (struct net_device*) ; 
 scalar_t__ is_valid_ether_addr (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gemini_ethernet_port*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  reset_control_reset (void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int gemini_ethernet_port_probe(struct platform_device *pdev)
{
	char *port_names[2] = { "ethernet0", "ethernet1" };
	struct gemini_ethernet_port *port;
	struct device *dev = &pdev->dev;
	struct gemini_ethernet *geth;
	struct net_device *netdev;
	struct resource *gmacres;
	struct resource *dmares;
	struct device *parent;
	unsigned int id;
	int irq;
	int ret;

	parent = dev->parent;
	geth = dev_get_drvdata(parent);

	if (!strcmp(dev_name(dev), "60008000.ethernet-port"))
		id = 0;
	else if (!strcmp(dev_name(dev), "6000c000.ethernet-port"))
		id = 1;
	else
		return -ENODEV;

	dev_info(dev, "probe %s ID %d\n", dev_name(dev), id);

	netdev = alloc_etherdev_mq(sizeof(*port), TX_QUEUE_NUM);
	if (!netdev) {
		dev_err(dev, "Can't allocate ethernet device #%d\n", id);
		return -ENOMEM;
	}

	port = netdev_priv(netdev);
	SET_NETDEV_DEV(netdev, dev);
	port->netdev = netdev;
	port->id = id;
	port->geth = geth;
	port->dev = dev;
	port->msg_enable = netif_msg_init(debug, DEFAULT_MSG_ENABLE);

	/* DMA memory */
	dmares = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!dmares) {
		dev_err(dev, "no DMA resource\n");
		return -ENODEV;
	}
	port->dma_base = devm_ioremap_resource(dev, dmares);
	if (IS_ERR(port->dma_base))
		return PTR_ERR(port->dma_base);

	/* GMAC config memory */
	gmacres = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!gmacres) {
		dev_err(dev, "no GMAC resource\n");
		return -ENODEV;
	}
	port->gmac_base = devm_ioremap_resource(dev, gmacres);
	if (IS_ERR(port->gmac_base))
		return PTR_ERR(port->gmac_base);

	/* Interrupt */
	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq ? irq : -ENODEV;
	port->irq = irq;

	/* Clock the port */
	port->pclk = devm_clk_get(dev, "PCLK");
	if (IS_ERR(port->pclk)) {
		dev_err(dev, "no PCLK\n");
		return PTR_ERR(port->pclk);
	}
	ret = clk_prepare_enable(port->pclk);
	if (ret)
		return ret;

	/* Maybe there is a nice ethernet address we should use */
	gemini_port_save_mac_addr(port);

	/* Reset the port */
	port->reset = devm_reset_control_get_exclusive(dev, NULL);
	if (IS_ERR(port->reset)) {
		dev_err(dev, "no reset\n");
		return PTR_ERR(port->reset);
	}
	reset_control_reset(port->reset);
	usleep_range(100, 500);

	/* Assign pointer in the main state container */
	if (!id)
		geth->port0 = port;
	else
		geth->port1 = port;

	/* This will just be done once both ports are up and reset */
	gemini_ethernet_init(geth);

	platform_set_drvdata(pdev, port);

	/* Set up and register the netdev */
	netdev->dev_id = port->id;
	netdev->irq = irq;
	netdev->netdev_ops = &gmac_351x_ops;
	netdev->ethtool_ops = &gmac_351x_ethtool_ops;

	spin_lock_init(&port->config_lock);
	gmac_clear_hw_stats(netdev);

	netdev->hw_features = GMAC_OFFLOAD_FEATURES;
	netdev->features |= GMAC_OFFLOAD_FEATURES | NETIF_F_GRO;
	/* We can handle jumbo frames up to 10236 bytes so, let's accept
	 * payloads of 10236 bytes minus VLAN and ethernet header
	 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = 10236 - VLAN_ETH_HLEN;

	port->freeq_refill = 0;
	netif_napi_add(netdev, &port->napi, gmac_napi_poll,
		       DEFAULT_NAPI_WEIGHT);

	if (is_valid_ether_addr((void *)port->mac_addr)) {
		memcpy(netdev->dev_addr, port->mac_addr, ETH_ALEN);
	} else {
		dev_dbg(dev, "ethernet address 0x%08x%08x%08x invalid\n",
			port->mac_addr[0], port->mac_addr[1],
			port->mac_addr[2]);
		dev_info(dev, "using a random ethernet address\n");
		eth_random_addr(netdev->dev_addr);
	}
	gmac_write_mac_address(netdev);

	ret = devm_request_threaded_irq(port->dev,
					port->irq,
					gemini_port_irq,
					gemini_port_irq_thread,
					IRQF_SHARED,
					port_names[port->id],
					port);
	if (ret)
		return ret;

	ret = register_netdev(netdev);
	if (!ret) {
		netdev_info(netdev,
			    "irq %d, DMA @ 0x%pap, GMAC @ 0x%pap\n",
			    port->irq, &dmares->start,
			    &gmacres->start);
		ret = gmac_setup_phy(netdev);
		if (ret)
			netdev_info(netdev,
				    "PHY init failed, deferring to ifup time\n");
		return 0;
	}

	port->netdev = NULL;
	free_netdev(netdev);
	return ret;
}