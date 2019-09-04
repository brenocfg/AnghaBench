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
struct timberdale_device {int /*<<< orphan*/  ctl_mapbase; int /*<<< orphan*/  ctl_membase; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPCTLSIZE ; 
 int /*<<< orphan*/  dev_attr_fw_ver ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct timberdale_device*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 struct timberdale_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timb_remove(struct pci_dev *dev)
{
	struct timberdale_device *priv = pci_get_drvdata(dev);

	mfd_remove_devices(&dev->dev);

	device_remove_file(&dev->dev, &dev_attr_fw_ver);

	iounmap(priv->ctl_membase);
	release_mem_region(priv->ctl_mapbase, CHIPCTLSIZE);

	pci_disable_msix(dev);
	pci_disable_device(dev);
	kfree(priv);
}