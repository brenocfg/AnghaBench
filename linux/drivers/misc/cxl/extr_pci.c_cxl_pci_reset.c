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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct cxl {scalar_t__ perst_same_image; TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cxl_data_cache_flush (struct cxl*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int pci_set_pcie_reset_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_warm_reset ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

int cxl_pci_reset(struct cxl *adapter)
{
	struct pci_dev *dev = to_pci_dev(adapter->dev.parent);
	int rc;

	if (adapter->perst_same_image) {
		dev_warn(&dev->dev,
			 "cxl: refusing to reset/reflash when perst_reloads_same_image is set.\n");
		return -EINVAL;
	}

	dev_info(&dev->dev, "CXL reset\n");

	/*
	 * The adapter is about to be reset, so ignore errors.
	 */
	cxl_data_cache_flush(adapter);

	/* pcie_warm_reset requests a fundamental pci reset which includes a
	 * PERST assert/deassert.  PERST triggers a loading of the image
	 * if "user" or "factory" is selected in sysfs */
	if ((rc = pci_set_pcie_reset_state(dev, pcie_warm_reset))) {
		dev_err(&dev->dev, "cxl: pcie_warm_reset failed\n");
		return rc;
	}

	return rc;
}