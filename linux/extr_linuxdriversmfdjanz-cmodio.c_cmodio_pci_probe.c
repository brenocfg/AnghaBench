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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_3__ dev; } ;
struct cmodio_device {TYPE_1__* ctrl; int /*<<< orphan*/  hex; struct pci_dev* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  int_disable; int /*<<< orphan*/  int_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cmodio_probe_submodules (struct cmodio_device*) ; 
 int /*<<< orphan*/  cmodio_sysfs_attr_group ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct cmodio_device* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (TYPE_1__*) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 TYPE_1__* pci_ioremap_bar (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct cmodio_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmodio_pci_probe(struct pci_dev *dev,
				      const struct pci_device_id *id)
{
	struct cmodio_device *priv;
	int ret;

	priv = devm_kzalloc(&dev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	pci_set_drvdata(dev, priv);
	priv->pdev = dev;

	/* Hardware Initialization */
	ret = pci_enable_device(dev);
	if (ret) {
		dev_err(&dev->dev, "unable to enable device\n");
		return ret;
	}

	pci_set_master(dev);
	ret = pci_request_regions(dev, DRV_NAME);
	if (ret) {
		dev_err(&dev->dev, "unable to request regions\n");
		goto out_pci_disable_device;
	}

	/* Onboard configuration registers */
	priv->ctrl = pci_ioremap_bar(dev, 4);
	if (!priv->ctrl) {
		dev_err(&dev->dev, "unable to remap onboard regs\n");
		ret = -ENOMEM;
		goto out_pci_release_regions;
	}

	/* Read the hex switch on the carrier board */
	priv->hex = ioread8(&priv->ctrl->int_enable);

	/* Add the MODULbus number (hex switch value) to the device's sysfs */
	ret = sysfs_create_group(&dev->dev.kobj, &cmodio_sysfs_attr_group);
	if (ret) {
		dev_err(&dev->dev, "unable to create sysfs attributes\n");
		goto out_unmap_ctrl;
	}

	/*
	 * Disable all interrupt lines, each submodule will enable its
	 * own interrupt line if needed
	 */
	iowrite8(0xf, &priv->ctrl->int_disable);

	/* Register drivers for all submodules */
	ret = cmodio_probe_submodules(priv);
	if (ret) {
		dev_err(&dev->dev, "unable to probe submodules\n");
		goto out_sysfs_remove_group;
	}

	return 0;

out_sysfs_remove_group:
	sysfs_remove_group(&dev->dev.kobj, &cmodio_sysfs_attr_group);
out_unmap_ctrl:
	iounmap(priv->ctrl);
out_pci_release_regions:
	pci_release_regions(dev);
out_pci_disable_device:
	pci_disable_device(dev);

	return ret;
}