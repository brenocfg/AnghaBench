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
struct pci_device_id {int vendor; int device; int /*<<< orphan*/  subvendor; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  subsystem_device; } ;
struct ddb {int has_dma; TYPE_2__* link; int /*<<< orphan*/  regs; struct pci_dev* pdev; int /*<<< orphan*/  regs_len; int /*<<< orphan*/ * dev; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int vendor; int device; int devid; int hwid; int regmapid; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; } ;
struct TYPE_5__ {TYPE_1__ ids; TYPE_3__* info; struct ddb* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BASE_READ ; 
 int /*<<< orphan*/  DMA_BASE_WRITE ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ ddb_init (struct ddb*) ; 
 int /*<<< orphan*/  ddb_irq_exit (struct ddb*) ; 
 int ddb_irq_init (struct ddb*) ; 
 int /*<<< orphan*/  ddb_msi_exit (struct ddb*) ; 
 int /*<<< orphan*/  ddb_unmap (struct ddb*) ; 
 int ddbreadl (struct ddb*,int) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 TYPE_3__* get_ddb_info (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ddb*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 struct ddb* vzalloc (int) ; 

__attribute__((used)) static int ddb_probe(struct pci_dev *pdev,
		     const struct pci_device_id *id)
{
	struct ddb *dev;
	int stat = 0;

	if (pci_enable_device(pdev) < 0)
		return -ENODEV;

	pci_set_master(pdev);

	if (pci_set_dma_mask(pdev, DMA_BIT_MASK(64)))
		if (pci_set_dma_mask(pdev, DMA_BIT_MASK(32)))
			return -ENODEV;

	dev = vzalloc(sizeof(*dev));
	if (!dev)
		return -ENOMEM;

	mutex_init(&dev->mutex);
	dev->has_dma = 1;
	dev->pdev = pdev;
	dev->dev = &pdev->dev;
	pci_set_drvdata(pdev, dev);

	dev->link[0].ids.vendor = id->vendor;
	dev->link[0].ids.device = id->device;
	dev->link[0].ids.subvendor = id->subvendor;
	dev->link[0].ids.subdevice = pdev->subsystem_device;
	dev->link[0].ids.devid = (id->device << 16) | id->vendor;

	dev->link[0].dev = dev;
	dev->link[0].info = get_ddb_info(id->vendor, id->device,
					 id->subvendor, pdev->subsystem_device);

	dev_info(&pdev->dev, "detected %s\n", dev->link[0].info->name);

	dev->regs_len = pci_resource_len(dev->pdev, 0);
	dev->regs = ioremap(pci_resource_start(dev->pdev, 0),
			    pci_resource_len(dev->pdev, 0));

	if (!dev->regs) {
		dev_err(&pdev->dev, "not enough memory for register map\n");
		stat = -ENOMEM;
		goto fail;
	}
	if (ddbreadl(dev, 0) == 0xffffffff) {
		dev_err(&pdev->dev, "cannot read registers\n");
		stat = -ENODEV;
		goto fail;
	}

	dev->link[0].ids.hwid = ddbreadl(dev, 0);
	dev->link[0].ids.regmapid = ddbreadl(dev, 4);

	dev_info(&pdev->dev, "HW %08x REGMAP %08x\n",
		 dev->link[0].ids.hwid, dev->link[0].ids.regmapid);

	ddbwritel(dev, 0, DMA_BASE_READ);
	ddbwritel(dev, 0, DMA_BASE_WRITE);

	stat = ddb_irq_init(dev);
	if (stat < 0)
		goto fail0;

	if (ddb_init(dev) == 0)
		return 0;

	ddb_irq_exit(dev);
fail0:
	dev_err(&pdev->dev, "fail0\n");
	ddb_msi_exit(dev);
fail:
	dev_err(&pdev->dev, "fail\n");

	ddb_unmap(dev);
	pci_set_drvdata(pdev, NULL);
	pci_disable_device(pdev);
	return -1;
}