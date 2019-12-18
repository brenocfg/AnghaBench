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
struct hnae3_ae_dev {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* handle_hw_ras_error ) (struct hnae3_ae_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 struct hnae3_ae_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_ae_dev*) ; 

__attribute__((used)) static pci_ers_result_t hns3_error_detected(struct pci_dev *pdev,
					    pci_channel_state_t state)
{
	struct hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);
	pci_ers_result_t ret;

	dev_info(&pdev->dev, "PCI error detected, state(=%d)!!\n", state);

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	if (!ae_dev || !ae_dev->ops) {
		dev_err(&pdev->dev,
			"Can't recover - error happened before device initialized\n");
		return PCI_ERS_RESULT_NONE;
	}

	if (ae_dev->ops->handle_hw_ras_error)
		ret = ae_dev->ops->handle_hw_ras_error(ae_dev);
	else
		return PCI_ERS_RESULT_NONE;

	return ret;
}