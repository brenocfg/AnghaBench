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
typedef  scalar_t__ ulong ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct gasket_dev {TYPE_1__ dev_info; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APEX_BAR2_REG_KERNEL_HIB_MSIX_TABLE_INIT ; 
 int /*<<< orphan*/  APEX_BAR2_REG_KERNEL_HIB_PAGE_TABLE_INIT ; 
 int /*<<< orphan*/  APEX_BAR_INDEX ; 
 int /*<<< orphan*/  APEX_RESET_DELAY ; 
 int APEX_RESET_RETRY ; 
 int ETIMEDOUT ; 
 scalar_t__ allow_power_save ; 
 int /*<<< orphan*/  apex_enter_reset (struct gasket_dev*) ; 
 int /*<<< orphan*/  apex_reset (struct gasket_dev*) ; 
 int /*<<< orphan*/  apex_sysfs_attrs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gasket_dev_read_64 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gasket_enable_device (struct gasket_dev*) ; 
 int gasket_pci_add_device (struct pci_dev*,struct gasket_dev**) ; 
 int /*<<< orphan*/  gasket_pci_remove_device (struct pci_dev*) ; 
 int gasket_sysfs_create_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct gasket_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apex_pci_probe(struct pci_dev *pci_dev,
			  const struct pci_device_id *id)
{
	int ret;
	ulong page_table_ready, msix_table_ready;
	int retries = 0;
	struct gasket_dev *gasket_dev;

	ret = pci_enable_device(pci_dev);
	if (ret) {
		dev_err(&pci_dev->dev, "error enabling PCI device\n");
		return ret;
	}

	pci_set_master(pci_dev);

	ret = gasket_pci_add_device(pci_dev, &gasket_dev);
	if (ret) {
		dev_err(&pci_dev->dev, "error adding gasket device\n");
		pci_disable_device(pci_dev);
		return ret;
	}

	pci_set_drvdata(pci_dev, gasket_dev);
	apex_reset(gasket_dev);

	while (retries < APEX_RESET_RETRY) {
		page_table_ready =
			gasket_dev_read_64(gasket_dev, APEX_BAR_INDEX,
					   APEX_BAR2_REG_KERNEL_HIB_PAGE_TABLE_INIT);
		msix_table_ready =
			gasket_dev_read_64(gasket_dev, APEX_BAR_INDEX,
					   APEX_BAR2_REG_KERNEL_HIB_MSIX_TABLE_INIT);
		if (page_table_ready && msix_table_ready)
			break;
		schedule_timeout(msecs_to_jiffies(APEX_RESET_DELAY));
		retries++;
	}

	if (retries == APEX_RESET_RETRY) {
		if (!page_table_ready)
			dev_err(gasket_dev->dev, "Page table init timed out\n");
		if (!msix_table_ready)
			dev_err(gasket_dev->dev, "MSI-X table init timed out\n");
		ret = -ETIMEDOUT;
		goto remove_device;
	}

	ret = gasket_sysfs_create_entries(gasket_dev->dev_info.device,
					  apex_sysfs_attrs);
	if (ret)
		dev_err(&pci_dev->dev, "error creating device sysfs entries\n");

	ret = gasket_enable_device(gasket_dev);
	if (ret) {
		dev_err(&pci_dev->dev, "error enabling gasket device\n");
		goto remove_device;
	}

	/* Place device in low power mode until opened */
	if (allow_power_save)
		apex_enter_reset(gasket_dev);

	return 0;

remove_device:
	gasket_pci_remove_device(pci_dev);
	pci_disable_device(pci_dev);
	return ret;
}