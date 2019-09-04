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
struct pci_driver {TYPE_1__* err_handler; int /*<<< orphan*/  name; } ;
struct eeh_dev {int /*<<< orphan*/  pdev; int /*<<< orphan*/  in_error; } ;
typedef  enum pci_ers_result { ____Placeholder_pci_ers_result } pci_ers_result ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  eeh_edev_info (struct eeh_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_uevent_ers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum pci_ers_result eeh_report_resume(struct eeh_dev *edev,
					     struct pci_driver *driver)
{
	if (!driver->err_handler->resume || !edev->in_error)
		return PCI_ERS_RESULT_NONE;

	eeh_edev_info(edev, "Invoking %s->resume()", driver->name);
	driver->err_handler->resume(edev->pdev);

	pci_uevent_ers(edev->pdev, PCI_ERS_RESULT_RECOVERED);
#ifdef CONFIG_PCI_IOV
	if (eeh_ops->notify_resume && eeh_dev_to_pdn(edev))
		eeh_ops->notify_resume(eeh_dev_to_pdn(edev));
#endif
	return PCI_ERS_RESULT_NONE;
}