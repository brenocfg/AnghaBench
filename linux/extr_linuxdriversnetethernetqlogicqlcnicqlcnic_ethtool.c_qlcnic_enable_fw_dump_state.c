#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_fw_dump {int enable; } ;
struct qlcnic_adapter {TYPE_1__* pdev; TYPE_2__* ahw; } ;
struct TYPE_5__ {struct qlcnic_fw_dump fw_dump; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  QLCRDX (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWRX (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_IDC_CTRL ; 
 int /*<<< orphan*/  QLC_83XX_IDC_DISABLE_FW_DUMP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qlcnic_83xx_lock_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_unlock_driver (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_84xx_check (struct qlcnic_adapter*) ; 

int qlcnic_enable_fw_dump_state(struct qlcnic_adapter *adapter)
{
	struct qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	u32 val;

	if (qlcnic_84xx_check(adapter)) {
		if (qlcnic_83xx_lock_driver(adapter))
			return -EBUSY;

		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		val &= ~QLC_83XX_IDC_DISABLE_FW_DUMP;
		QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);

		qlcnic_83xx_unlock_driver(adapter);
	} else {
		fw_dump->enable = true;
	}

	dev_info(&adapter->pdev->dev, "FW dump enabled\n");

	return 0;
}