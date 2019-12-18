#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct net_device {int irq; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int phy_id; int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct ks_net {char const* hw_addr; char const* hw_addr_cmd; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  msg_enable; TYPE_1__ mii; int /*<<< orphan*/  statelock; int /*<<< orphan*/  lock; struct platform_device* pdev; struct net_device* netdev; } ;
struct ks8851_mll_platform_data {int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int CIDER_ID ; 
 int CIDER_REV_MASK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GRR_GSR ; 
 scalar_t__ IS_ERR (char const*) ; 
 int /*<<< orphan*/  KS_CIDER ; 
 int /*<<< orphan*/  KS_OBCR ; 
 int NETIF_MSG_DRV ; 
 int NETIF_MSG_LINK ; 
 int NETIF_MSG_PROBE ; 
 int OBCR_ODS_16mA ; 
 int PTR_ERR (char const*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_2__*) ; 
 struct net_device* alloc_etherdev (int) ; 
 struct ks8851_mll_platform_data* dev_get_platdata (TYPE_2__*) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_disable_qmu (struct ks_net*) ; 
 int /*<<< orphan*/  ks_ethtool_ops ; 
 int /*<<< orphan*/  ks_hw_init (struct ks_net*) ; 
 int /*<<< orphan*/  ks_netdev_ops ; 
 int /*<<< orphan*/  ks_phy_read ; 
 int /*<<< orphan*/  ks_phy_write ; 
 int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_read_config (struct ks_net*) ; 
 scalar_t__ ks_read_selftest (struct ks_net*) ; 
 int /*<<< orphan*/  ks_set_mac (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_setup (struct ks_net*) ; 
 int /*<<< orphan*/  ks_setup_int (struct ks_net*) ; 
 int /*<<< orphan*/  ks_soft_reset (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_enable ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int) ; 
 char* of_get_mac_address (scalar_t__) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ks8851_probe(struct platform_device *pdev)
{
	int err;
	struct net_device *netdev;
	struct ks_net *ks;
	u16 id, data;
	const char *mac;

	netdev = alloc_etherdev(sizeof(struct ks_net));
	if (!netdev)
		return -ENOMEM;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	ks = netdev_priv(netdev);
	ks->netdev = netdev;

	ks->hw_addr = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(ks->hw_addr)) {
		err = PTR_ERR(ks->hw_addr);
		goto err_free;
	}

	ks->hw_addr_cmd = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(ks->hw_addr_cmd)) {
		err = PTR_ERR(ks->hw_addr_cmd);
		goto err_free;
	}

	netdev->irq = platform_get_irq(pdev, 0);

	if ((int)netdev->irq < 0) {
		err = netdev->irq;
		goto err_free;
	}

	ks->pdev = pdev;

	mutex_init(&ks->lock);
	spin_lock_init(&ks->statelock);

	netdev->netdev_ops = &ks_netdev_ops;
	netdev->ethtool_ops = &ks_ethtool_ops;

	/* setup mii state */
	ks->mii.dev             = netdev;
	ks->mii.phy_id          = 1,
	ks->mii.phy_id_mask     = 1;
	ks->mii.reg_num_mask    = 0xf;
	ks->mii.mdio_read       = ks_phy_read;
	ks->mii.mdio_write      = ks_phy_write;

	netdev_info(netdev, "message enable is %d\n", msg_enable);
	/* set the default message enable */
	ks->msg_enable = netif_msg_init(msg_enable, (NETIF_MSG_DRV |
						     NETIF_MSG_PROBE |
						     NETIF_MSG_LINK));
	ks_read_config(ks);

	/* simple check for a valid chip being connected to the bus */
	if ((ks_rdreg16(ks, KS_CIDER) & ~CIDER_REV_MASK) != CIDER_ID) {
		netdev_err(netdev, "failed to read device ID\n");
		err = -ENODEV;
		goto err_free;
	}

	if (ks_read_selftest(ks)) {
		netdev_err(netdev, "failed to read device ID\n");
		err = -ENODEV;
		goto err_free;
	}

	err = register_netdev(netdev);
	if (err)
		goto err_free;

	platform_set_drvdata(pdev, netdev);

	ks_soft_reset(ks, GRR_GSR);
	ks_hw_init(ks);
	ks_disable_qmu(ks);
	ks_setup(ks);
	ks_setup_int(ks);

	data = ks_rdreg16(ks, KS_OBCR);
	ks_wrreg16(ks, KS_OBCR, data | OBCR_ODS_16mA);

	/* overwriting the default MAC address */
	if (pdev->dev.of_node) {
		mac = of_get_mac_address(pdev->dev.of_node);
		if (!IS_ERR(mac))
			ether_addr_copy(ks->mac_addr, mac);
	} else {
		struct ks8851_mll_platform_data *pdata;

		pdata = dev_get_platdata(&pdev->dev);
		if (!pdata) {
			netdev_err(netdev, "No platform data\n");
			err = -ENODEV;
			goto err_pdata;
		}
		memcpy(ks->mac_addr, pdata->mac_addr, ETH_ALEN);
	}
	if (!is_valid_ether_addr(ks->mac_addr)) {
		/* Use random MAC address if none passed */
		eth_random_addr(ks->mac_addr);
		netdev_info(netdev, "Using random mac address\n");
	}
	netdev_info(netdev, "Mac address is: %pM\n", ks->mac_addr);

	memcpy(netdev->dev_addr, ks->mac_addr, ETH_ALEN);

	ks_set_mac(ks, netdev->dev_addr);

	id = ks_rdreg16(ks, KS_CIDER);

	netdev_info(netdev, "Found chip, family: 0x%x, id: 0x%x, rev: 0x%x\n",
		    (id >> 8) & 0xff, (id >> 4) & 0xf, (id >> 1) & 0x7);
	return 0;

err_pdata:
	unregister_netdev(netdev);
err_free:
	free_netdev(netdev);
	return err;
}