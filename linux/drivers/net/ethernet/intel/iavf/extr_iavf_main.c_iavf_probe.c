#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int devfn; TYPE_2__* bus; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  arq_mutex; int /*<<< orphan*/  asq_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_id; int /*<<< orphan*/  func; int /*<<< orphan*/  device; } ;
struct iavf_hw {TYPE_3__ aq; TYPE_1__ bus; int /*<<< orphan*/  subsystem_device_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  hw_addr; struct iavf_adapter* back; } ;
struct iavf_adapter {int /*<<< orphan*/  down_waitqueue; int /*<<< orphan*/  init_task; int /*<<< orphan*/  client_task; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  adminq_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  cloud_filter_list; int /*<<< orphan*/  vlan_filter_list; int /*<<< orphan*/  mac_filter_list; int /*<<< orphan*/  cloud_filter_list_lock; int /*<<< orphan*/  mac_vlan_list_lock; int /*<<< orphan*/  state; scalar_t__ msg_enable; struct iavf_hw hw; struct pci_dev* pdev; struct net_device* netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_DEBUG_LEVEL_SHIFT ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IAVF_MAX_REQ_QUEUES ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __IAVF_STARTUP ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iavf_adminq_task ; 
 int /*<<< orphan*/  iavf_client_task ; 
 int /*<<< orphan*/  iavf_driver_name ; 
 int /*<<< orphan*/  iavf_init_task ; 
 int /*<<< orphan*/  iavf_reset_task ; 
 int /*<<< orphan*/  iavf_watchdog_task ; 
 int /*<<< orphan*/  iavf_wq ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iavf_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct net_device *netdev;
	struct iavf_adapter *adapter = NULL;
	struct iavf_hw *hw = NULL;
	int err;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (err) {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev,
				"DMA configuration failed: 0x%x\n", err);
			goto err_dma;
		}
	}

	err = pci_request_regions(pdev, iavf_driver_name);
	if (err) {
		dev_err(&pdev->dev,
			"pci_request_regions failed 0x%x\n", err);
		goto err_pci_reg;
	}

	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);

	netdev = alloc_etherdev_mq(sizeof(struct iavf_adapter),
				   IAVF_MAX_REQ_QUEUES);
	if (!netdev) {
		err = -ENOMEM;
		goto err_alloc_etherdev;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);

	adapter->netdev = netdev;
	adapter->pdev = pdev;

	hw = &adapter->hw;
	hw->back = adapter;

	adapter->msg_enable = BIT(DEFAULT_DEBUG_LEVEL_SHIFT) - 1;
	adapter->state = __IAVF_STARTUP;

	/* Call save state here because it relies on the adapter struct. */
	pci_save_state(pdev);

	hw->hw_addr = ioremap(pci_resource_start(pdev, 0),
			      pci_resource_len(pdev, 0));
	if (!hw->hw_addr) {
		err = -EIO;
		goto err_ioremap;
	}
	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	pci_read_config_byte(pdev, PCI_REVISION_ID, &hw->revision_id);
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_device_id = pdev->subsystem_device;
	hw->bus.device = PCI_SLOT(pdev->devfn);
	hw->bus.func = PCI_FUNC(pdev->devfn);
	hw->bus.bus_id = pdev->bus->number;

	/* set up the locks for the AQ, do this only once in probe
	 * and destroy them only once in remove
	 */
	mutex_init(&hw->aq.asq_mutex);
	mutex_init(&hw->aq.arq_mutex);

	spin_lock_init(&adapter->mac_vlan_list_lock);
	spin_lock_init(&adapter->cloud_filter_list_lock);

	INIT_LIST_HEAD(&adapter->mac_filter_list);
	INIT_LIST_HEAD(&adapter->vlan_filter_list);
	INIT_LIST_HEAD(&adapter->cloud_filter_list);

	INIT_WORK(&adapter->reset_task, iavf_reset_task);
	INIT_WORK(&adapter->adminq_task, iavf_adminq_task);
	INIT_DELAYED_WORK(&adapter->watchdog_task, iavf_watchdog_task);
	INIT_DELAYED_WORK(&adapter->client_task, iavf_client_task);
	INIT_DELAYED_WORK(&adapter->init_task, iavf_init_task);
	queue_delayed_work(iavf_wq, &adapter->init_task,
			   msecs_to_jiffies(5 * (pdev->devfn & 0x07)));

	/* Setup the wait queue for indicating transition to down status */
	init_waitqueue_head(&adapter->down_waitqueue);

	return 0;

err_ioremap:
	free_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	return err;
}