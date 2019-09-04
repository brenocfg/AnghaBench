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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CRB_DRV_IDC_VER ; 
 scalar_t__ QLCNIC_DRV_IDC_VER ; 
 scalar_t__ QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int qlcnic_check_idc_ver(struct qlcnic_adapter *adapter)
{
	u32 val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_IDC_VER);

	if (val != QLCNIC_DRV_IDC_VER) {
		dev_warn(&adapter->pdev->dev, "IDC Version mismatch, driver's"
			" idc ver = %x; reqd = %x\n", QLCNIC_DRV_IDC_VER, val);
	}

	return 0;
}