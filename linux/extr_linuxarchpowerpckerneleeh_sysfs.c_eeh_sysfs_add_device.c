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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct eeh_dev {int mode; } ;

/* Variables and functions */
 int EEH_DEV_SYSFS ; 
 int /*<<< orphan*/  dev_attr_eeh_mode ; 
 int /*<<< orphan*/  dev_attr_eeh_pe_config_addr ; 
 int /*<<< orphan*/  dev_attr_eeh_pe_state ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeh_enabled () ; 
 scalar_t__ eeh_notify_resume_add (struct pci_dev*) ; 
 struct eeh_dev* pci_dev_to_eeh_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void eeh_sysfs_add_device(struct pci_dev *pdev)
{
	struct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	int rc=0;

	if (!eeh_enabled())
		return;

	if (edev && (edev->mode & EEH_DEV_SYSFS))
		return;

	rc += device_create_file(&pdev->dev, &dev_attr_eeh_mode);
	rc += device_create_file(&pdev->dev, &dev_attr_eeh_pe_config_addr);
	rc += device_create_file(&pdev->dev, &dev_attr_eeh_pe_state);
	rc += eeh_notify_resume_add(pdev);

	if (rc)
		pr_warn("EEH: Unable to create sysfs entries\n");
	else if (edev)
		edev->mode |= EEH_DEV_SYSFS;
}