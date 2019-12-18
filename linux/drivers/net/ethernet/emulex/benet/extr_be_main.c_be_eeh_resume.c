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
struct pci_dev {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DETECTION_DELAY ; 
 int be_resume (struct be_adapter*) ; 
 int /*<<< orphan*/  be_roce_dev_add (struct be_adapter*) ; 
 int /*<<< orphan*/  be_schedule_err_detection (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct be_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 

__attribute__((used)) static void be_eeh_resume(struct pci_dev *pdev)
{
	int status = 0;
	struct be_adapter *adapter = pci_get_drvdata(pdev);

	dev_info(&adapter->pdev->dev, "EEH resume\n");

	pci_save_state(pdev);

	status = be_resume(adapter);
	if (status)
		goto err;

	be_roce_dev_add(adapter);

	be_schedule_err_detection(adapter, ERR_DETECTION_DELAY);
	return;
err:
	dev_err(&adapter->pdev->dev, "EEH resume failed\n");
}