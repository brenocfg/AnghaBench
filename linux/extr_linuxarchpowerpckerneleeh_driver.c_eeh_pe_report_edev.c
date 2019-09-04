#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_driver {int /*<<< orphan*/  name; int /*<<< orphan*/  err_handler; } ;
struct eeh_dev {int mode; TYPE_1__* pdev; int /*<<< orphan*/  pe; } ;
typedef  enum pci_ers_result { ____Placeholder_pci_ers_result } pci_ers_result ;
typedef  int (* eeh_report_fn ) (struct eeh_dev*,struct pci_driver*) ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEH_DEV_NO_HANDLER ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeh_dev_removed (struct eeh_dev*) ; 
 scalar_t__ eeh_edev_actionable (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_edev_info (struct eeh_dev*,char*,...) ; 
 struct pci_driver* eeh_pcid_get (TYPE_1__*) ; 
 int /*<<< orphan*/  eeh_pcid_put (TYPE_1__*) ; 
 int /*<<< orphan*/  eeh_pe_passed (int /*<<< orphan*/ ) ; 
 int pci_ers_merge_result (int,int) ; 
 int /*<<< orphan*/  pci_ers_result_name (int) ; 

__attribute__((used)) static void eeh_pe_report_edev(struct eeh_dev *edev, eeh_report_fn fn,
			       enum pci_ers_result *result)
{
	struct pci_driver *driver;
	enum pci_ers_result new_result;

	device_lock(&edev->pdev->dev);
	if (eeh_edev_actionable(edev)) {
		driver = eeh_pcid_get(edev->pdev);

		if (!driver)
			eeh_edev_info(edev, "no driver");
		else if (!driver->err_handler)
			eeh_edev_info(edev, "driver not EEH aware");
		else if (edev->mode & EEH_DEV_NO_HANDLER)
			eeh_edev_info(edev, "driver bound too late");
		else {
			new_result = fn(edev, driver);
			eeh_edev_info(edev, "%s driver reports: '%s'",
				      driver->name,
				      pci_ers_result_name(new_result));
			if (result)
				*result = pci_ers_merge_result(*result,
							       new_result);
		}
		if (driver)
			eeh_pcid_put(edev->pdev);
	} else {
		eeh_edev_info(edev, "not actionable (%d,%d,%d)", !!edev->pdev,
			      !eeh_dev_removed(edev), !eeh_pe_passed(edev->pe));
	}
	device_unlock(&edev->pdev->dev);
}