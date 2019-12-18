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
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {scalar_t__ error_state; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct fm10k_intfc {scalar_t__ uc_addr; scalar_t__ sw_addr; int /*<<< orphan*/  state; struct pci_dev* pdev; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  macvlan_task; int /*<<< orphan*/  service_task; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FM10K_UC_ADDR_SIZE ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __FM10K_SERVICE_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net_device* fm10k_alloc_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_clear_queueing_scheme (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_dbg_intfc_init (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_driver_name ; 
 int fm10k_hw_ready (struct fm10k_intfc*) ; 
 int /*<<< orphan*/ * fm10k_info_tbl ; 
 int fm10k_init_queueing_scheme (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_iov_configure (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_macvlan_task ; 
 int /*<<< orphan*/  fm10k_mbx_free_irq (struct fm10k_intfc*) ; 
 int fm10k_mbx_request_irq (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_service_event_schedule (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_service_task ; 
 int /*<<< orphan*/  fm10k_service_timer ; 
 int fm10k_sw_init (struct fm10k_intfc*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 scalar_t__ pci_channel_io_normal ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int pci_request_mem_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fm10k_intfc*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_print_link_status (struct pci_dev*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm10k_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct net_device *netdev;
	struct fm10k_intfc *interface;
	int err;

	if (pdev->error_state != pci_channel_io_normal) {
		dev_err(&pdev->dev,
			"PCI device still in an error state. Unable to load...\n");
		return -EIO;
	}

	err = pci_enable_device_mem(pdev);
	if (err) {
		dev_err(&pdev->dev,
			"PCI enable device failed: %d\n", err);
		return err;
	}

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	if (err)
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (err) {
		dev_err(&pdev->dev,
			"DMA configuration failed: %d\n", err);
		goto err_dma;
	}

	err = pci_request_mem_regions(pdev, fm10k_driver_name);
	if (err) {
		dev_err(&pdev->dev,
			"pci_request_selected_regions failed: %d\n", err);
		goto err_pci_reg;
	}

	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);
	pci_save_state(pdev);

	netdev = fm10k_alloc_netdev(fm10k_info_tbl[ent->driver_data]);
	if (!netdev) {
		err = -ENOMEM;
		goto err_alloc_netdev;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	interface = netdev_priv(netdev);
	pci_set_drvdata(pdev, interface);

	interface->netdev = netdev;
	interface->pdev = pdev;

	interface->uc_addr = ioremap(pci_resource_start(pdev, 0),
				     FM10K_UC_ADDR_SIZE);
	if (!interface->uc_addr) {
		err = -EIO;
		goto err_ioremap;
	}

	err = fm10k_sw_init(interface, ent);
	if (err)
		goto err_sw_init;

	/* enable debugfs support */
	fm10k_dbg_intfc_init(interface);

	err = fm10k_init_queueing_scheme(interface);
	if (err)
		goto err_sw_init;

	/* the mbx interrupt might attempt to schedule the service task, so we
	 * must ensure it is disabled since we haven't yet requested the timer
	 * or work item.
	 */
	set_bit(__FM10K_SERVICE_DISABLE, interface->state);

	err = fm10k_mbx_request_irq(interface);
	if (err)
		goto err_mbx_interrupt;

	/* final check of hardware state before registering the interface */
	err = fm10k_hw_ready(interface);
	if (err)
		goto err_register;

	err = register_netdev(netdev);
	if (err)
		goto err_register;

	/* carrier off reporting is important to ethtool even BEFORE open */
	netif_carrier_off(netdev);

	/* stop all the transmit queues from transmitting until link is up */
	netif_tx_stop_all_queues(netdev);

	/* Initialize service timer and service task late in order to avoid
	 * cleanup issues.
	 */
	timer_setup(&interface->service_timer, fm10k_service_timer, 0);
	INIT_WORK(&interface->service_task, fm10k_service_task);

	/* Setup the MAC/VLAN queue */
	INIT_DELAYED_WORK(&interface->macvlan_task, fm10k_macvlan_task);

	/* kick off service timer now, even when interface is down */
	mod_timer(&interface->service_timer, (HZ * 2) + jiffies);

	/* print warning for non-optimal configurations */
	pcie_print_link_status(interface->pdev);

	/* report MAC address for logging */
	dev_info(&pdev->dev, "%pM\n", netdev->dev_addr);

	/* enable SR-IOV after registering netdev to enforce PF/VF ordering */
	fm10k_iov_configure(pdev, 0);

	/* clear the service task disable bit and kick off service task */
	clear_bit(__FM10K_SERVICE_DISABLE, interface->state);
	fm10k_service_event_schedule(interface);

	return 0;

err_register:
	fm10k_mbx_free_irq(interface);
err_mbx_interrupt:
	fm10k_clear_queueing_scheme(interface);
err_sw_init:
	if (interface->sw_addr)
		iounmap(interface->sw_addr);
	iounmap(interface->uc_addr);
err_ioremap:
	free_netdev(netdev);
err_alloc_netdev:
	pci_release_mem_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	return err;
}