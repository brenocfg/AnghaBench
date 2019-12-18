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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct cmodio_device {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmodio_sysfs_attr_group ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct cmodio_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmodio_pci_remove(struct pci_dev *dev)
{
	struct cmodio_device *priv = pci_get_drvdata(dev);

	mfd_remove_devices(&dev->dev);
	sysfs_remove_group(&dev->dev.kobj, &cmodio_sysfs_attr_group);
	iounmap(priv->ctrl);
	pci_release_regions(dev);
	pci_disable_device(dev);
}