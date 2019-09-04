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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QLCNIC_FWERROR_CODE (int) ; 
 scalar_t__ QLCNIC_FWERROR_FAN_FAILURE ; 
 int /*<<< orphan*/  QLCNIC_PEG_HALT_STATUS1 ; 
 int QLCNIC_RCODE_FATAL_ERROR ; 
 int QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int qlcnic_83xx_idc_check_fan_failure(struct qlcnic_adapter *adapter)
{
	u32 status;

	status = QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_HALT_STATUS1);

	if (status & QLCNIC_RCODE_FATAL_ERROR) {
		dev_err(&adapter->pdev->dev,
			"peg halt status1=0x%x\n", status);
		if (QLCNIC_FWERROR_CODE(status) == QLCNIC_FWERROR_FAN_FAILURE) {
			dev_err(&adapter->pdev->dev,
				"On board active cooling fan failed. "
				"Device has been halted.\n");
			dev_err(&adapter->pdev->dev,
				"Replace the adapter.\n");
			return -EIO;
		}
	}

	return 0;
}