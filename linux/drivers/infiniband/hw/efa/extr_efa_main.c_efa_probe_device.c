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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  msix_vector_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  msix_vector_idx; } ;
struct efa_com_dev {int /*<<< orphan*/  reg_bar; TYPE_2__ aenq; TYPE_1__ aq; int /*<<< orphan*/ * dmadev; struct efa_dev* efa_dev; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  admin_msix_vector_idx; void* reg_bar_len; void* reg_bar_addr; void* mem_bar_len; void* mem_bar_addr; struct pci_dev* pdev; struct efa_com_dev edev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int EFAULT ; 
 int EFA_BASE_BAR_MASK ; 
 int /*<<< orphan*/  EFA_MEM_BAR ; 
 int /*<<< orphan*/  EFA_REG_BAR ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct efa_dev* ERR_PTR (int) ; 
 int ETIME ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  aenq_handlers ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int efa_com_admin_init (struct efa_com_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efa_com_mmio_reg_read_destroy (struct efa_com_dev*) ; 
 int efa_com_mmio_reg_read_init (struct efa_com_dev*) ; 
 int /*<<< orphan*/  efa_dev ; 
 int efa_device_init (struct efa_com_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  efa_disable_msix (struct efa_dev*) ; 
 int efa_enable_msix (struct efa_dev*) ; 
 int /*<<< orphan*/  efa_free_mgmnt_irq (struct efa_dev*) ; 
 int /*<<< orphan*/  efa_release_bars (struct efa_dev*,int) ; 
 int efa_set_mgmnt_irq (struct efa_dev*) ; 
 struct efa_dev* ib_alloc_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdev ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int pci_request_selected_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 void* pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 void* pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct efa_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static struct efa_dev *efa_probe_device(struct pci_dev *pdev)
{
	struct efa_com_dev *edev;
	struct efa_dev *dev;
	int bars;
	int err;

	err = pci_enable_device_mem(pdev);
	if (err) {
		dev_err(&pdev->dev, "pci_enable_device_mem() failed!\n");
		return ERR_PTR(err);
	}

	pci_set_master(pdev);

	dev = ib_alloc_device(efa_dev, ibdev);
	if (!dev) {
		dev_err(&pdev->dev, "Device alloc failed\n");
		err = -ENOMEM;
		goto err_disable_device;
	}

	pci_set_drvdata(pdev, dev);
	edev = &dev->edev;
	edev->efa_dev = dev;
	edev->dmadev = &pdev->dev;
	dev->pdev = pdev;

	bars = pci_select_bars(pdev, IORESOURCE_MEM) & EFA_BASE_BAR_MASK;
	err = pci_request_selected_regions(pdev, bars, DRV_MODULE_NAME);
	if (err) {
		dev_err(&pdev->dev, "pci_request_selected_regions failed %d\n",
			err);
		goto err_ibdev_destroy;
	}

	dev->reg_bar_addr = pci_resource_start(pdev, EFA_REG_BAR);
	dev->reg_bar_len = pci_resource_len(pdev, EFA_REG_BAR);
	dev->mem_bar_addr = pci_resource_start(pdev, EFA_MEM_BAR);
	dev->mem_bar_len = pci_resource_len(pdev, EFA_MEM_BAR);

	edev->reg_bar = devm_ioremap(&pdev->dev,
				     dev->reg_bar_addr,
				     dev->reg_bar_len);
	if (!edev->reg_bar) {
		dev_err(&pdev->dev, "Failed to remap register bar\n");
		err = -EFAULT;
		goto err_release_bars;
	}

	err = efa_com_mmio_reg_read_init(edev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init readless MMIO\n");
		goto err_iounmap;
	}

	err = efa_device_init(edev, pdev);
	if (err) {
		dev_err(&pdev->dev, "EFA device init failed\n");
		if (err == -ETIME)
			err = -EPROBE_DEFER;
		goto err_reg_read_destroy;
	}

	err = efa_enable_msix(dev);
	if (err)
		goto err_reg_read_destroy;

	edev->aq.msix_vector_idx = dev->admin_msix_vector_idx;
	edev->aenq.msix_vector_idx = dev->admin_msix_vector_idx;

	err = efa_set_mgmnt_irq(dev);
	if (err)
		goto err_disable_msix;

	err = efa_com_admin_init(edev, &aenq_handlers);
	if (err)
		goto err_free_mgmnt_irq;

	return dev;

err_free_mgmnt_irq:
	efa_free_mgmnt_irq(dev);
err_disable_msix:
	efa_disable_msix(dev);
err_reg_read_destroy:
	efa_com_mmio_reg_read_destroy(edev);
err_iounmap:
	devm_iounmap(&pdev->dev, edev->reg_bar);
err_release_bars:
	efa_release_bars(dev, EFA_BASE_BAR_MASK);
err_ibdev_destroy:
	ib_dealloc_device(&dev->ibdev);
err_disable_device:
	pci_disable_device(pdev);
	return ERR_PTR(err);
}