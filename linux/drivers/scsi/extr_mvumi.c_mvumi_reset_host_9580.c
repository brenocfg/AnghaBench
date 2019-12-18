#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mvumi_hba {TYPE_2__* pdev; TYPE_1__* regs; int /*<<< orphan*/  fw_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  reset_request; int /*<<< orphan*/  reset_enable; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  FW_STATE_ABORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mvumi_pci_set_master (TYPE_2__*) ; 
 int /*<<< orphan*/  mvumi_restore_bar_addr (struct mvumi_hba*) ; 
 int mvumi_wait_for_fw (struct mvumi_hba*) ; 
 int mvumi_wait_for_outstanding (struct mvumi_hba*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_2__*) ; 
 scalar_t__ pci_enable_device (TYPE_2__*) ; 

__attribute__((used)) static int mvumi_reset_host_9580(struct mvumi_hba *mhba)
{
	mhba->fw_state = FW_STATE_ABORT;

	iowrite32(0, mhba->regs->reset_enable);
	iowrite32(0xf, mhba->regs->reset_request);

	iowrite32(0x10, mhba->regs->reset_enable);
	iowrite32(0x10, mhba->regs->reset_request);
	msleep(100);
	pci_disable_device(mhba->pdev);

	if (pci_enable_device(mhba->pdev)) {
		dev_err(&mhba->pdev->dev, "enable device failed\n");
		return FAILED;
	}
	if (mvumi_pci_set_master(mhba->pdev)) {
		dev_err(&mhba->pdev->dev, "set master failed\n");
		return FAILED;
	}
	mvumi_restore_bar_addr(mhba);
	if (mvumi_wait_for_fw(mhba) == FAILED)
		return FAILED;

	return mvumi_wait_for_outstanding(mhba);
}