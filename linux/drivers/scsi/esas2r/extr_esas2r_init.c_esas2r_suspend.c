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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct esas2r_adapter {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ESAS2R_LOG_INFO ; 
 int /*<<< orphan*/  esas2r_adapter_power_down (struct esas2r_adapter*,int) ; 
 int /*<<< orphan*/  esas2r_log_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

int esas2r_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	u32 device_state;
	struct esas2r_adapter *a = (struct esas2r_adapter *)host->hostdata;

	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev), "suspending adapter()");
	if (!a)
		return -ENODEV;

	esas2r_adapter_power_down(a, 1);
	device_state = pci_choose_state(pdev, state);
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "pci_save_state() called");
	pci_save_state(pdev);
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "pci_disable_device() called");
	pci_disable_device(pdev);
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "pci_set_power_state() called");
	pci_set_power_state(pdev, device_state);
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev), "esas2r_suspend(): 0");
	return 0;
}