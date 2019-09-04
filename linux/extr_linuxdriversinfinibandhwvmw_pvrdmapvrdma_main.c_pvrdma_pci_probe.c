#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_19__ {unsigned long pfn; void* map; scalar_t__ index; } ;
struct TYPE_21__ {int /*<<< orphan*/  dir_dma; int /*<<< orphan*/ * pages; } ;
struct TYPE_20__ {int /*<<< orphan*/  notifier_call; } ;
struct pvrdma_dev {int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  device_link; void* regs; TYPE_5__ driver_uar; scalar_t__ dsrbase; TYPE_10__* dsr; TYPE_7__ async_pdir; TYPE_7__ cq_pdir; TYPE_9__* netdev; int /*<<< orphan*/  sgid_tbl; TYPE_6__ nb_netdev; int /*<<< orphan*/  cq_ring_state; int /*<<< orphan*/  async_ring_state; void* resp_slot; void* cmd_slot; void* dsr_version; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_22__ {int /*<<< orphan*/  name; } ;
struct TYPE_18__ {unsigned long long gid_tbl_len; } ;
struct TYPE_17__ {int /*<<< orphan*/  pdir_dma; void* num_pages; } ;
struct TYPE_16__ {int /*<<< orphan*/  pdir_dma; void* num_pages; } ;
struct TYPE_15__ {int gos_ver; int /*<<< orphan*/  gos_type; int /*<<< orphan*/  gos_bits; } ;
struct TYPE_14__ {unsigned long uar_pfn; int cmd_slot_dma; int resp_slot_dma; TYPE_4__ caps; TYPE_3__ cq_ring_pages; TYPE_2__ async_ring_pages; TYPE_1__ gos_info; int /*<<< orphan*/  driver_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long long IORESOURCE_MEM ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_DEVICE_ID_VMWARE_VMXNET3 ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_VMWARE ; 
 int /*<<< orphan*/  PVRDMA_DEVICE_CTL_ACTIVATE ; 
 int /*<<< orphan*/  PVRDMA_GOS_BITS_32 ; 
 int /*<<< orphan*/  PVRDMA_GOS_BITS_64 ; 
 int /*<<< orphan*/  PVRDMA_GOS_TYPE_LINUX ; 
 void* PVRDMA_NUM_RING_PAGES ; 
 int PVRDMA_PCI_RESOURCE_REG ; 
 int PVRDMA_PCI_RESOURCE_UAR ; 
 int /*<<< orphan*/  PVRDMA_REG_CTL ; 
 int /*<<< orphan*/  PVRDMA_REG_DSRHIGH ; 
 int /*<<< orphan*/  PVRDMA_REG_DSRLOW ; 
 int /*<<< orphan*/  PVRDMA_REG_ERR ; 
 int /*<<< orphan*/  PVRDMA_REG_VERSION ; 
 int /*<<< orphan*/  PVRDMA_SUPPORTED (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  PVRDMA_VERSION ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_hold (TYPE_9__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_put (TYPE_9__*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,unsigned long,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_10__*,scalar_t__) ; 
 TYPE_10__* dma_zalloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_alloc_device (int) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 void* ioremap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kcalloc (unsigned long long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 TYPE_9__* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long long pci_resource_flags (struct pci_dev*,int) ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pvrdma_alloc_intrs (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_device_list ; 
 int /*<<< orphan*/  pvrdma_device_list_lock ; 
 int /*<<< orphan*/  pvrdma_disable_intrs (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_enable_intrs (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_free_irq (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_free_slots (struct pvrdma_dev*) ; 
 int pvrdma_init_device (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_netdevice_event ; 
 int /*<<< orphan*/  pvrdma_page_dir_cleanup (struct pvrdma_dev*,TYPE_7__*) ; 
 int pvrdma_page_dir_init (struct pvrdma_dev*,TYPE_7__*,void*,int) ; 
 void* pvrdma_read_reg (struct pvrdma_dev*,int /*<<< orphan*/ ) ; 
 int pvrdma_register_device (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_uar_table_cleanup (struct pvrdma_dev*) ; 
 int pvrdma_uar_table_init (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_write_reg (struct pvrdma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdevice_notifier (TYPE_6__*) ; 

__attribute__((used)) static int pvrdma_pci_probe(struct pci_dev *pdev,
			    const struct pci_device_id *id)
{
	struct pci_dev *pdev_net;
	struct pvrdma_dev *dev;
	int ret;
	unsigned long start;
	unsigned long len;
	dma_addr_t slot_dma = 0;

	dev_dbg(&pdev->dev, "initializing driver %s\n", pci_name(pdev));

	/* Allocate zero-out device */
	dev = (struct pvrdma_dev *)ib_alloc_device(sizeof(*dev));
	if (!dev) {
		dev_err(&pdev->dev, "failed to allocate IB device\n");
		return -ENOMEM;
	}

	mutex_lock(&pvrdma_device_list_lock);
	list_add(&dev->device_link, &pvrdma_device_list);
	mutex_unlock(&pvrdma_device_list_lock);

	ret = pvrdma_init_device(dev);
	if (ret)
		goto err_free_device;

	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);

	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		goto err_free_device;
	}

	dev_dbg(&pdev->dev, "PCI resource flags BAR0 %#lx\n",
		pci_resource_flags(pdev, 0));
	dev_dbg(&pdev->dev, "PCI resource len %#llx\n",
		(unsigned long long)pci_resource_len(pdev, 0));
	dev_dbg(&pdev->dev, "PCI resource start %#llx\n",
		(unsigned long long)pci_resource_start(pdev, 0));
	dev_dbg(&pdev->dev, "PCI resource flags BAR1 %#lx\n",
		pci_resource_flags(pdev, 1));
	dev_dbg(&pdev->dev, "PCI resource len %#llx\n",
		(unsigned long long)pci_resource_len(pdev, 1));
	dev_dbg(&pdev->dev, "PCI resource start %#llx\n",
		(unsigned long long)pci_resource_start(pdev, 1));

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
	    !(pci_resource_flags(pdev, 1) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev, "PCI BAR region not MMIO\n");
		ret = -ENOMEM;
		goto err_free_device;
	}

	ret = pci_request_regions(pdev, DRV_NAME);
	if (ret) {
		dev_err(&pdev->dev, "cannot request PCI resources\n");
		goto err_disable_pdev;
	}

	/* Enable 64-Bit DMA */
	if (pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) == 0) {
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		if (ret != 0) {
			dev_err(&pdev->dev,
				"pci_set_consistent_dma_mask failed\n");
			goto err_free_resource;
		}
	} else {
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (ret != 0) {
			dev_err(&pdev->dev,
				"pci_set_dma_mask failed\n");
			goto err_free_resource;
		}
	}

	pci_set_master(pdev);

	/* Map register space */
	start = pci_resource_start(dev->pdev, PVRDMA_PCI_RESOURCE_REG);
	len = pci_resource_len(dev->pdev, PVRDMA_PCI_RESOURCE_REG);
	dev->regs = ioremap(start, len);
	if (!dev->regs) {
		dev_err(&pdev->dev, "register mapping failed\n");
		ret = -ENOMEM;
		goto err_free_resource;
	}

	/* Setup per-device UAR. */
	dev->driver_uar.index = 0;
	dev->driver_uar.pfn =
		pci_resource_start(dev->pdev, PVRDMA_PCI_RESOURCE_UAR) >>
		PAGE_SHIFT;
	dev->driver_uar.map =
		ioremap(dev->driver_uar.pfn << PAGE_SHIFT, PAGE_SIZE);
	if (!dev->driver_uar.map) {
		dev_err(&pdev->dev, "failed to remap UAR pages\n");
		ret = -ENOMEM;
		goto err_unmap_regs;
	}

	dev->dsr_version = pvrdma_read_reg(dev, PVRDMA_REG_VERSION);
	dev_info(&pdev->dev, "device version %d, driver version %d\n",
		 dev->dsr_version, PVRDMA_VERSION);

	dev->dsr = dma_zalloc_coherent(&pdev->dev, sizeof(*dev->dsr),
				       &dev->dsrbase, GFP_KERNEL);
	if (!dev->dsr) {
		dev_err(&pdev->dev, "failed to allocate shared region\n");
		ret = -ENOMEM;
		goto err_uar_unmap;
	}

	/* Setup the shared region */
	dev->dsr->driver_version = PVRDMA_VERSION;
	dev->dsr->gos_info.gos_bits = sizeof(void *) == 4 ?
		PVRDMA_GOS_BITS_32 :
		PVRDMA_GOS_BITS_64;
	dev->dsr->gos_info.gos_type = PVRDMA_GOS_TYPE_LINUX;
	dev->dsr->gos_info.gos_ver = 1;
	dev->dsr->uar_pfn = dev->driver_uar.pfn;

	/* Command slot. */
	dev->cmd_slot = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					   &slot_dma, GFP_KERNEL);
	if (!dev->cmd_slot) {
		ret = -ENOMEM;
		goto err_free_dsr;
	}

	dev->dsr->cmd_slot_dma = (u64)slot_dma;

	/* Response slot. */
	dev->resp_slot = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					    &slot_dma, GFP_KERNEL);
	if (!dev->resp_slot) {
		ret = -ENOMEM;
		goto err_free_slots;
	}

	dev->dsr->resp_slot_dma = (u64)slot_dma;

	/* Async event ring */
	dev->dsr->async_ring_pages.num_pages = PVRDMA_NUM_RING_PAGES;
	ret = pvrdma_page_dir_init(dev, &dev->async_pdir,
				   dev->dsr->async_ring_pages.num_pages, true);
	if (ret)
		goto err_free_slots;
	dev->async_ring_state = dev->async_pdir.pages[0];
	dev->dsr->async_ring_pages.pdir_dma = dev->async_pdir.dir_dma;

	/* CQ notification ring */
	dev->dsr->cq_ring_pages.num_pages = PVRDMA_NUM_RING_PAGES;
	ret = pvrdma_page_dir_init(dev, &dev->cq_pdir,
				   dev->dsr->cq_ring_pages.num_pages, true);
	if (ret)
		goto err_free_async_ring;
	dev->cq_ring_state = dev->cq_pdir.pages[0];
	dev->dsr->cq_ring_pages.pdir_dma = dev->cq_pdir.dir_dma;

	/*
	 * Write the PA of the shared region to the device. The writes must be
	 * ordered such that the high bits are written last. When the writes
	 * complete, the device will have filled out the capabilities.
	 */

	pvrdma_write_reg(dev, PVRDMA_REG_DSRLOW, (u32)dev->dsrbase);
	pvrdma_write_reg(dev, PVRDMA_REG_DSRHIGH,
			 (u32)((u64)(dev->dsrbase) >> 32));

	/* Make sure the write is complete before reading status. */
	mb();

	/* The driver supports RoCE V1 and V2. */
	if (!PVRDMA_SUPPORTED(dev)) {
		dev_err(&pdev->dev, "driver needs RoCE v1 or v2 support\n");
		ret = -EFAULT;
		goto err_free_cq_ring;
	}

	/* Paired vmxnet3 will have same bus, slot. But func will be 0 */
	pdev_net = pci_get_slot(pdev->bus, PCI_DEVFN(PCI_SLOT(pdev->devfn), 0));
	if (!pdev_net) {
		dev_err(&pdev->dev, "failed to find paired net device\n");
		ret = -ENODEV;
		goto err_free_cq_ring;
	}

	if (pdev_net->vendor != PCI_VENDOR_ID_VMWARE ||
	    pdev_net->device != PCI_DEVICE_ID_VMWARE_VMXNET3) {
		dev_err(&pdev->dev, "failed to find paired vmxnet3 device\n");
		pci_dev_put(pdev_net);
		ret = -ENODEV;
		goto err_free_cq_ring;
	}

	dev->netdev = pci_get_drvdata(pdev_net);
	pci_dev_put(pdev_net);
	if (!dev->netdev) {
		dev_err(&pdev->dev, "failed to get vmxnet3 device\n");
		ret = -ENODEV;
		goto err_free_cq_ring;
	}
	dev_hold(dev->netdev);

	dev_info(&pdev->dev, "paired device to %s\n", dev->netdev->name);

	/* Interrupt setup */
	ret = pvrdma_alloc_intrs(dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to allocate interrupts\n");
		ret = -ENOMEM;
		goto err_free_cq_ring;
	}

	/* Allocate UAR table. */
	ret = pvrdma_uar_table_init(dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to allocate UAR table\n");
		ret = -ENOMEM;
		goto err_free_intrs;
	}

	/* Allocate GID table */
	dev->sgid_tbl = kcalloc(dev->dsr->caps.gid_tbl_len,
				sizeof(union ib_gid), GFP_KERNEL);
	if (!dev->sgid_tbl) {
		ret = -ENOMEM;
		goto err_free_uar_table;
	}
	dev_dbg(&pdev->dev, "gid table len %d\n", dev->dsr->caps.gid_tbl_len);

	pvrdma_enable_intrs(dev);

	/* Activate pvrdma device */
	pvrdma_write_reg(dev, PVRDMA_REG_CTL, PVRDMA_DEVICE_CTL_ACTIVATE);

	/* Make sure the write is complete before reading status. */
	mb();

	/* Check if device was successfully activated */
	ret = pvrdma_read_reg(dev, PVRDMA_REG_ERR);
	if (ret != 0) {
		dev_err(&pdev->dev, "failed to activate device\n");
		ret = -EFAULT;
		goto err_disable_intr;
	}

	/* Register IB device */
	ret = pvrdma_register_device(dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to register IB device\n");
		goto err_disable_intr;
	}

	dev->nb_netdev.notifier_call = pvrdma_netdevice_event;
	ret = register_netdevice_notifier(&dev->nb_netdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to register netdevice events\n");
		goto err_unreg_ibdev;
	}

	dev_info(&pdev->dev, "attached to device\n");
	return 0;

err_unreg_ibdev:
	ib_unregister_device(&dev->ib_dev);
err_disable_intr:
	pvrdma_disable_intrs(dev);
	kfree(dev->sgid_tbl);
err_free_uar_table:
	pvrdma_uar_table_cleanup(dev);
err_free_intrs:
	pvrdma_free_irq(dev);
	pci_free_irq_vectors(pdev);
err_free_cq_ring:
	if (dev->netdev) {
		dev_put(dev->netdev);
		dev->netdev = NULL;
	}
	pvrdma_page_dir_cleanup(dev, &dev->cq_pdir);
err_free_async_ring:
	pvrdma_page_dir_cleanup(dev, &dev->async_pdir);
err_free_slots:
	pvrdma_free_slots(dev);
err_free_dsr:
	dma_free_coherent(&pdev->dev, sizeof(*dev->dsr), dev->dsr,
			  dev->dsrbase);
err_uar_unmap:
	iounmap(dev->driver_uar.map);
err_unmap_regs:
	iounmap(dev->regs);
err_free_resource:
	pci_release_regions(pdev);
err_disable_pdev:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
err_free_device:
	mutex_lock(&pvrdma_device_list_lock);
	list_del(&dev->device_link);
	mutex_unlock(&pvrdma_device_list_lock);
	ib_dealloc_device(&dev->ib_dev);
	return ret;
}