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
struct pci_dev {int dummy; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DETECTION_DELAY ; 
 int be_resume (struct be_adapter*) ; 
 int /*<<< orphan*/  be_schedule_err_detection (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct be_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 

__attribute__((used)) static int be_pci_resume(struct pci_dev *pdev)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);
	int status = 0;

	status = pci_enable_device(pdev);
	if (status)
		return status;

	pci_restore_state(pdev);

	status = be_resume(adapter);
	if (status)
		return status;

	be_schedule_err_detection(adapter, ERR_DETECTION_DELAY);

	return 0;
}