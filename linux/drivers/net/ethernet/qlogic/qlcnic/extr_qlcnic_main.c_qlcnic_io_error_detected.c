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
struct qlcnic_hardware_ops {int /*<<< orphan*/  (* io_error_detected ) (struct pci_dev*,int /*<<< orphan*/ ) ;} ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int /*<<< orphan*/  pci_channel_state_t ;
struct TYPE_2__ {struct qlcnic_hardware_ops* hw_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pci_ers_result_t qlcnic_io_error_detected(struct pci_dev *pdev,
						 pci_channel_state_t state)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	struct qlcnic_hardware_ops *hw_ops = adapter->ahw->hw_ops;

	if (hw_ops->io_error_detected) {
		return hw_ops->io_error_detected(pdev, state);
	} else {
		dev_err(&pdev->dev, "AER error_detected handler not registered.\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}
}