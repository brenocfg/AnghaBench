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
typedef  int /*<<< orphan*/  u32 ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int max; } ;
struct TYPE_4__ {TYPE_1__ cbs; } ;
struct nic {int msg_enable; scalar_t__ mac; int* eeprom; int /*<<< orphan*/  csr; struct net_device* netdev; int /*<<< orphan*/  cbs_pool; TYPE_2__ params; struct pci_dev* pdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  watchdog; int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  mdio_ctrl; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  features; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  priv_flags; } ;
struct csr {int dummy; } ;
struct cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  E100_NAPI_WEIGHT ; 
 int /*<<< orphan*/  E100_WATCHDOG_PERIOD ; 
 int EAGAIN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IFF_SUPP_NOFCS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  NETIF_F_RXALL ; 
 int /*<<< orphan*/  NETIF_F_RXFCS ; 
 int /*<<< orphan*/  NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int debug ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_pool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int e100_alloc (struct nic*) ; 
 int e100_eeprom_load (struct nic*) ; 
 int /*<<< orphan*/  e100_ethtool_ops ; 
 int /*<<< orphan*/  e100_free (struct nic*) ; 
 int /*<<< orphan*/  e100_get_defaults (struct nic*) ; 
 int /*<<< orphan*/  e100_hw_reset (struct nic*) ; 
 int /*<<< orphan*/  e100_netdev_ops ; 
 int /*<<< orphan*/  e100_phy_init (struct nic*) ; 
 int /*<<< orphan*/  e100_poll ; 
 int /*<<< orphan*/  e100_tx_timeout_task ; 
 int /*<<< orphan*/  e100_watchdog ; 
 int /*<<< orphan*/  eeprom_bad_csum_allow ; 
 size_t eeprom_id ; 
 int eeprom_id_wol ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ich ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ mac_82558_D101_A4 ; 
 int /*<<< orphan*/  mdio_ctrl_hw ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct nic*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_info (struct nic*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pme_active (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  probe ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 scalar_t__ use_io ; 
 int /*<<< orphan*/  wol_magic ; 

__attribute__((used)) static int e100_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct net_device *netdev;
	struct nic *nic;
	int err;

	if (!(netdev = alloc_etherdev(sizeof(struct nic))))
		return -ENOMEM;

	netdev->hw_features |= NETIF_F_RXFCS;
	netdev->priv_flags |= IFF_SUPP_NOFCS;
	netdev->hw_features |= NETIF_F_RXALL;

	netdev->netdev_ops = &e100_netdev_ops;
	netdev->ethtool_ops = &e100_ethtool_ops;
	netdev->watchdog_timeo = E100_WATCHDOG_PERIOD;
	strncpy(netdev->name, pci_name(pdev), sizeof(netdev->name) - 1);

	nic = netdev_priv(netdev);
	netif_napi_add(netdev, &nic->napi, e100_poll, E100_NAPI_WEIGHT);
	nic->netdev = netdev;
	nic->pdev = pdev;
	nic->msg_enable = (1 << debug) - 1;
	nic->mdio_ctrl = mdio_ctrl_hw;
	pci_set_drvdata(pdev, netdev);

	if ((err = pci_enable_device(pdev))) {
		netif_err(nic, probe, nic->netdev, "Cannot enable PCI device, aborting\n");
		goto err_out_free_dev;
	}

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		netif_err(nic, probe, nic->netdev, "Cannot find proper PCI device base address, aborting\n");
		err = -ENODEV;
		goto err_out_disable_pdev;
	}

	if ((err = pci_request_regions(pdev, DRV_NAME))) {
		netif_err(nic, probe, nic->netdev, "Cannot obtain PCI resources, aborting\n");
		goto err_out_disable_pdev;
	}

	if ((err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32)))) {
		netif_err(nic, probe, nic->netdev, "No usable DMA configuration, aborting\n");
		goto err_out_free_res;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	if (use_io)
		netif_info(nic, probe, nic->netdev, "using i/o access mode\n");

	nic->csr = pci_iomap(pdev, (use_io ? 1 : 0), sizeof(struct csr));
	if (!nic->csr) {
		netif_err(nic, probe, nic->netdev, "Cannot map device registers, aborting\n");
		err = -ENOMEM;
		goto err_out_free_res;
	}

	if (ent->driver_data)
		nic->flags |= ich;
	else
		nic->flags &= ~ich;

	e100_get_defaults(nic);

	/* D100 MAC doesn't allow rx of vlan packets with normal MTU */
	if (nic->mac < mac_82558_D101_A4)
		netdev->features |= NETIF_F_VLAN_CHALLENGED;

	/* locks must be initialized before calling hw_reset */
	spin_lock_init(&nic->cb_lock);
	spin_lock_init(&nic->cmd_lock);
	spin_lock_init(&nic->mdio_lock);

	/* Reset the device before pci_set_master() in case device is in some
	 * funky state and has an interrupt pending - hint: we don't have the
	 * interrupt handler registered yet. */
	e100_hw_reset(nic);

	pci_set_master(pdev);

	timer_setup(&nic->watchdog, e100_watchdog, 0);

	INIT_WORK(&nic->tx_timeout_task, e100_tx_timeout_task);

	if ((err = e100_alloc(nic))) {
		netif_err(nic, probe, nic->netdev, "Cannot alloc driver memory, aborting\n");
		goto err_out_iounmap;
	}

	if ((err = e100_eeprom_load(nic)))
		goto err_out_free;

	e100_phy_init(nic);

	memcpy(netdev->dev_addr, nic->eeprom, ETH_ALEN);
	if (!is_valid_ether_addr(netdev->dev_addr)) {
		if (!eeprom_bad_csum_allow) {
			netif_err(nic, probe, nic->netdev, "Invalid MAC address from EEPROM, aborting\n");
			err = -EAGAIN;
			goto err_out_free;
		} else {
			netif_err(nic, probe, nic->netdev, "Invalid MAC address from EEPROM, you MUST configure one.\n");
		}
	}

	/* Wol magic packet can be enabled from eeprom */
	if ((nic->mac >= mac_82558_D101_A4) &&
	   (nic->eeprom[eeprom_id] & eeprom_id_wol)) {
		nic->flags |= wol_magic;
		device_set_wakeup_enable(&pdev->dev, true);
	}

	/* ack any pending wake events, disable PME */
	pci_pme_active(pdev, false);

	strcpy(netdev->name, "eth%d");
	if ((err = register_netdev(netdev))) {
		netif_err(nic, probe, nic->netdev, "Cannot register net device, aborting\n");
		goto err_out_free;
	}
	nic->cbs_pool = dma_pool_create(netdev->name,
			   &nic->pdev->dev,
			   nic->params.cbs.max * sizeof(struct cb),
			   sizeof(u32),
			   0);
	if (!nic->cbs_pool) {
		netif_err(nic, probe, nic->netdev, "Cannot create DMA pool, aborting\n");
		err = -ENOMEM;
		goto err_out_pool;
	}
	netif_info(nic, probe, nic->netdev,
		   "addr 0x%llx, irq %d, MAC addr %pM\n",
		   (unsigned long long)pci_resource_start(pdev, use_io ? 1 : 0),
		   pdev->irq, netdev->dev_addr);

	return 0;

err_out_pool:
	unregister_netdev(netdev);
err_out_free:
	e100_free(nic);
err_out_iounmap:
	pci_iounmap(pdev, nic->csr);
err_out_free_res:
	pci_release_regions(pdev);
err_out_disable_pdev:
	pci_disable_device(pdev);
err_out_free_dev:
	free_netdev(netdev);
	return err;
}