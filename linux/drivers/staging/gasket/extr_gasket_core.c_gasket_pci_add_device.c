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
struct device {int /*<<< orphan*/  kobj; } ;
struct pci_dev {struct device dev; } ;
struct gasket_internal_desc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct gasket_dev {int /*<<< orphan*/  dev; TYPE_2__ dev_info; struct pci_dev* pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 int __gasket_add_device (struct device*,struct gasket_internal_desc*,struct gasket_dev**) ; 
 int /*<<< orphan*/  __gasket_remove_device (struct gasket_internal_desc*,struct gasket_dev*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  g_mutex ; 
 int /*<<< orphan*/  gasket_cleanup_pci (struct gasket_dev*) ; 
 int gasket_setup_pci (struct pci_dev*,struct gasket_dev*) ; 
 struct gasket_internal_desc* lookup_pci_internal_desc (struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gasket_pci_add_device(struct pci_dev *pci_dev,
			  struct gasket_dev **gasket_devp)
{
	int ret;
	struct gasket_internal_desc *internal_desc;
	struct gasket_dev *gasket_dev;
	struct device *parent;

	dev_dbg(&pci_dev->dev, "add PCI gasket device\n");

	mutex_lock(&g_mutex);
	internal_desc = lookup_pci_internal_desc(pci_dev);
	mutex_unlock(&g_mutex);
	if (!internal_desc) {
		dev_err(&pci_dev->dev,
			"PCI add device called for unknown driver type\n");
		return -ENODEV;
	}

	parent = &pci_dev->dev;
	ret = __gasket_add_device(parent, internal_desc, &gasket_dev);
	if (ret)
		return ret;

	gasket_dev->pci_dev = pci_dev;
	ret = gasket_setup_pci(pci_dev, gasket_dev);
	if (ret)
		goto cleanup_pci;

	/*
	 * Once we've created the mapping structures successfully, attempt to
	 * create a symlink to the pci directory of this object.
	 */
	ret = sysfs_create_link(&gasket_dev->dev_info.device->kobj,
				&pci_dev->dev.kobj, dev_name(&pci_dev->dev));
	if (ret) {
		dev_err(gasket_dev->dev,
			"Cannot create sysfs pci link: %d\n", ret);
		goto cleanup_pci;
	}

	*gasket_devp = gasket_dev;
	return 0;

cleanup_pci:
	gasket_cleanup_pci(gasket_dev);
	__gasket_remove_device(internal_desc, gasket_dev);
	return ret;
}