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
struct smsc911x_platform_config {struct smsc911x_platform_config* mac; scalar_t__ shift; } ;
struct smsc911x_data {int msg_enable; int /*<<< orphan*/ * ioaddr; int /*<<< orphan*/  mac_lock; struct smsc911x_platform_config config; int /*<<< orphan*/ * ops; struct net_device* dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int irq; struct smsc911x_platform_config* dev_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMSC_CHIPNAME ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 struct net_device* alloc_etherdev (int) ; 
 int debug ; 
 struct smsc911x_platform_config* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 scalar_t__ is_valid_ether_addr (struct smsc911x_platform_config*) ; 
 int /*<<< orphan*/  memcpy (struct smsc911x_platform_config*,struct smsc911x_platform_config*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,struct smsc911x_platform_config*) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  probe ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  shifted_smsc911x_ops ; 
 int /*<<< orphan*/  smsc911x_disable_resources (struct platform_device*) ; 
 int smsc911x_enable_resources (struct platform_device*) ; 
 int /*<<< orphan*/  smsc911x_free_resources (struct platform_device*) ; 
 int smsc911x_init (struct net_device*) ; 
 int smsc911x_mii_init (struct platform_device*,struct net_device*) ; 
 int smsc911x_probe_config (struct smsc911x_platform_config*,int /*<<< orphan*/ *) ; 
 int smsc911x_request_resources (struct platform_device*) ; 
 int /*<<< orphan*/  smsc911x_set_hw_mac_address (struct smsc911x_data*,struct smsc911x_platform_config*) ; 
 int /*<<< orphan*/  smsc_get_mac (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  standard_smsc911x_ops ; 

__attribute__((used)) static int smsc911x_drv_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct smsc911x_data *pdata;
	struct smsc911x_platform_config *config = dev_get_platdata(&pdev->dev);
	struct resource *res;
	int res_size, irq;
	int retval;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "smsc911x-memory");
	if (!res)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		pr_warn("Could not allocate resource\n");
		retval = -ENODEV;
		goto out_0;
	}
	res_size = resource_size(res);

	irq = platform_get_irq(pdev, 0);
	if (irq == -EPROBE_DEFER) {
		retval = -EPROBE_DEFER;
		goto out_0;
	} else if (irq <= 0) {
		pr_warn("Could not allocate irq resource\n");
		retval = -ENODEV;
		goto out_0;
	}

	if (!request_mem_region(res->start, res_size, SMSC_CHIPNAME)) {
		retval = -EBUSY;
		goto out_0;
	}

	dev = alloc_etherdev(sizeof(struct smsc911x_data));
	if (!dev) {
		retval = -ENOMEM;
		goto out_release_io_1;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);

	pdata = netdev_priv(dev);
	dev->irq = irq;
	pdata->ioaddr = ioremap_nocache(res->start, res_size);
	if (!pdata->ioaddr) {
		retval = -ENOMEM;
		goto out_ioremap_fail;
	}

	pdata->dev = dev;
	pdata->msg_enable = ((1 << debug) - 1);

	platform_set_drvdata(pdev, dev);

	retval = smsc911x_request_resources(pdev);
	if (retval)
		goto out_request_resources_fail;

	retval = smsc911x_enable_resources(pdev);
	if (retval)
		goto out_enable_resources_fail;

	if (pdata->ioaddr == NULL) {
		SMSC_WARN(pdata, probe, "Error smsc911x base address invalid");
		retval = -ENOMEM;
		goto out_disable_resources;
	}

	retval = smsc911x_probe_config(&pdata->config, &pdev->dev);
	if (retval && config) {
		/* copy config parameters across to pdata */
		memcpy(&pdata->config, config, sizeof(pdata->config));
		retval = 0;
	}

	if (retval) {
		SMSC_WARN(pdata, probe, "Error smsc911x config not found");
		goto out_disable_resources;
	}

	/* assume standard, non-shifted, access to HW registers */
	pdata->ops = &standard_smsc911x_ops;
	/* apply the right access if shifting is needed */
	if (pdata->config.shift)
		pdata->ops = &shifted_smsc911x_ops;

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	retval = smsc911x_init(dev);
	if (retval < 0)
		goto out_disable_resources;

	netif_carrier_off(dev);

	retval = smsc911x_mii_init(pdev, dev);
	if (retval) {
		SMSC_WARN(pdata, probe, "Error %i initialising mii", retval);
		goto out_disable_resources;
	}

	retval = register_netdev(dev);
	if (retval) {
		SMSC_WARN(pdata, probe, "Error %i registering device", retval);
		goto out_disable_resources;
	} else {
		SMSC_TRACE(pdata, probe,
			   "Network interface: \"%s\"", dev->name);
	}

	spin_lock_irq(&pdata->mac_lock);

	/* Check if mac address has been specified when bringing interface up */
	if (is_valid_ether_addr(dev->dev_addr)) {
		smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
		SMSC_TRACE(pdata, probe,
			   "MAC Address is specified by configuration");
	} else if (is_valid_ether_addr(pdata->config.mac)) {
		memcpy(dev->dev_addr, pdata->config.mac, ETH_ALEN);
		SMSC_TRACE(pdata, probe,
			   "MAC Address specified by platform data");
	} else {
		/* Try reading mac address from device. if EEPROM is present
		 * it will already have been set */
		smsc_get_mac(dev);

		if (is_valid_ether_addr(dev->dev_addr)) {
			/* eeprom values are valid  so use them */
			SMSC_TRACE(pdata, probe,
				   "Mac Address is read from LAN911x EEPROM");
		} else {
			/* eeprom values are invalid, generate random MAC */
			eth_hw_addr_random(dev);
			smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
			SMSC_TRACE(pdata, probe,
				   "MAC Address is set to eth_random_addr");
		}
	}

	spin_unlock_irq(&pdata->mac_lock);

	netdev_info(dev, "MAC Address: %pM\n", dev->dev_addr);

	return 0;

out_disable_resources:
	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	(void)smsc911x_disable_resources(pdev);
out_enable_resources_fail:
	smsc911x_free_resources(pdev);
out_request_resources_fail:
	iounmap(pdata->ioaddr);
out_ioremap_fail:
	free_netdev(dev);
out_release_io_1:
	release_mem_region(res->start, resource_size(res));
out_0:
	return retval;
}