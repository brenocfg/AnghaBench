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
struct ql_mpi_coredump {int dummy; } ;
struct ql_adapter {int /*<<< orphan*/  mpi_mutex; int /*<<< orphan*/  ide_completion; int /*<<< orphan*/  mpi_core_to_log; int /*<<< orphan*/  mpi_idc_work; int /*<<< orphan*/  mpi_port_cfg_work; int /*<<< orphan*/  mpi_work; int /*<<< orphan*/  mpi_reset_work; int /*<<< orphan*/  asic_reset_work; int /*<<< orphan*/  workqueue; void* tx_max_coalesced_frames; void* rx_max_coalesced_frames; void* tx_coalesce_usecs; void* rx_coalesce_usecs; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  current_mac_addr; TYPE_1__* nic_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/ * mpi_coredump; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  msg_enable; void* doorbell_area; int /*<<< orphan*/  doorbell_area_size; void* reg_base; struct pci_dev* pdev; struct net_device* ndev; } ;
struct pci_dev {int needs_freset; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int (* get_flash ) (struct ql_adapter*) ;} ;

/* Variables and functions */
 void* DFLT_COALESCE_WAIT ; 
 void* DFLT_INTER_FRAME_WAIT ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_STRING ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_RX_RING_ENTRIES ; 
 int /*<<< orphan*/  NUM_TX_RING_ENTRIES ; 
 int /*<<< orphan*/  QL_DMA64 ; 
 int /*<<< orphan*/  QL_FRC_COREDUMP ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  default_msg ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcie_set_readrq (struct pci_dev*,int) ; 
 int /*<<< orphan*/  ql_asic_reset_work ; 
 int ql_get_board_info (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_mpi_core_to_log ; 
 int /*<<< orphan*/  ql_mpi_idc_work ; 
 int /*<<< orphan*/  ql_mpi_port_cfg_work ; 
 int /*<<< orphan*/  ql_mpi_reset_work ; 
 int /*<<< orphan*/  ql_mpi_work ; 
 int /*<<< orphan*/  ql_release_all (struct pci_dev*) ; 
 scalar_t__ qlge_force_coredump ; 
 scalar_t__ qlge_mpi_coredump ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct ql_adapter*) ; 
 int /*<<< orphan*/ * vmalloc (int) ; 

__attribute__((used)) static int ql_init_device(struct pci_dev *pdev, struct net_device *ndev,
			  int cards_found)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	int err = 0;

	memset((void *)qdev, 0, sizeof(*qdev));
	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "PCI device enable failed.\n");
		return err;
	}

	qdev->ndev = ndev;
	qdev->pdev = pdev;
	pci_set_drvdata(pdev, ndev);

	/* Set PCIe read request size */
	err = pcie_set_readrq(pdev, 4096);
	if (err) {
		dev_err(&pdev->dev, "Set readrq failed.\n");
		goto err_out1;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(&pdev->dev, "PCI region request failed.\n");
		return err;
	}

	pci_set_master(pdev);
	if (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) {
		set_bit(QL_DMA64, &qdev->flags);
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	} else {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (!err)
		       err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	}

	if (err) {
		dev_err(&pdev->dev, "No usable DMA configuration.\n");
		goto err_out2;
	}

	/* Set PCIe reset type for EEH to fundamental. */
	pdev->needs_freset = 1;
	pci_save_state(pdev);
	qdev->reg_base =
	    ioremap_nocache(pci_resource_start(pdev, 1),
			    pci_resource_len(pdev, 1));
	if (!qdev->reg_base) {
		dev_err(&pdev->dev, "Register mapping failed.\n");
		err = -ENOMEM;
		goto err_out2;
	}

	qdev->doorbell_area_size = pci_resource_len(pdev, 3);
	qdev->doorbell_area =
	    ioremap_nocache(pci_resource_start(pdev, 3),
			    pci_resource_len(pdev, 3));
	if (!qdev->doorbell_area) {
		dev_err(&pdev->dev, "Doorbell register mapping failed.\n");
		err = -ENOMEM;
		goto err_out2;
	}

	err = ql_get_board_info(qdev);
	if (err) {
		dev_err(&pdev->dev, "Register access failed.\n");
		err = -EIO;
		goto err_out2;
	}
	qdev->msg_enable = netif_msg_init(debug, default_msg);
	spin_lock_init(&qdev->hw_lock);
	spin_lock_init(&qdev->stats_lock);

	if (qlge_mpi_coredump) {
		qdev->mpi_coredump =
			vmalloc(sizeof(struct ql_mpi_coredump));
		if (qdev->mpi_coredump == NULL) {
			err = -ENOMEM;
			goto err_out2;
		}
		if (qlge_force_coredump)
			set_bit(QL_FRC_COREDUMP, &qdev->flags);
	}
	/* make sure the EEPROM is good */
	err = qdev->nic_ops->get_flash(qdev);
	if (err) {
		dev_err(&pdev->dev, "Invalid FLASH.\n");
		goto err_out2;
	}

	/* Keep local copy of current mac address. */
	memcpy(qdev->current_mac_addr, ndev->dev_addr, ndev->addr_len);

	/* Set up the default ring sizes. */
	qdev->tx_ring_size = NUM_TX_RING_ENTRIES;
	qdev->rx_ring_size = NUM_RX_RING_ENTRIES;

	/* Set up the coalescing parameters. */
	qdev->rx_coalesce_usecs = DFLT_COALESCE_WAIT;
	qdev->tx_coalesce_usecs = DFLT_COALESCE_WAIT;
	qdev->rx_max_coalesced_frames = DFLT_INTER_FRAME_WAIT;
	qdev->tx_max_coalesced_frames = DFLT_INTER_FRAME_WAIT;

	/*
	 * Set up the operating parameters.
	 */
	qdev->workqueue = alloc_ordered_workqueue("%s", WQ_MEM_RECLAIM,
						  ndev->name);
	if (!qdev->workqueue) {
		err = -ENOMEM;
		goto err_out2;
	}

	INIT_DELAYED_WORK(&qdev->asic_reset_work, ql_asic_reset_work);
	INIT_DELAYED_WORK(&qdev->mpi_reset_work, ql_mpi_reset_work);
	INIT_DELAYED_WORK(&qdev->mpi_work, ql_mpi_work);
	INIT_DELAYED_WORK(&qdev->mpi_port_cfg_work, ql_mpi_port_cfg_work);
	INIT_DELAYED_WORK(&qdev->mpi_idc_work, ql_mpi_idc_work);
	INIT_DELAYED_WORK(&qdev->mpi_core_to_log, ql_mpi_core_to_log);
	init_completion(&qdev->ide_completion);
	mutex_init(&qdev->mpi_mutex);

	if (!cards_found) {
		dev_info(&pdev->dev, "%s\n", DRV_STRING);
		dev_info(&pdev->dev, "Driver name: %s, Version: %s.\n",
			 DRV_NAME, DRV_VERSION);
	}
	return 0;
err_out2:
	ql_release_all(pdev);
err_out1:
	pci_disable_device(pdev);
	return err;
}