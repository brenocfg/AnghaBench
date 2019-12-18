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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  state; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_POLL_DELAY ; 
 int /*<<< orphan*/  QLCNIC_CRB_DEV_STATE ; 
 scalar_t__ QLCNIC_DEV_READY ; 
 scalar_t__ QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_AER ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qlcnic_fw_poll_work ; 
 int /*<<< orphan*/  qlcnic_schedule_work (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_82xx_io_resume(struct pci_dev *pdev)
{
	u32 state;
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	if (state == QLCNIC_DEV_READY && test_and_clear_bit(__QLCNIC_AER,
							    &adapter->state))
		qlcnic_schedule_work(adapter, qlcnic_fw_poll_work,
				     FW_POLL_DELAY);
}