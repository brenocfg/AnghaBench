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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  flags; scalar_t__ fw_fail_cnt; int /*<<< orphan*/  portnum; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_ACTIVE ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_STATE ; 
 int QLCNIC_DEV_COLD ; 
 int QLCNIC_DEV_FAILED ; 
 int /*<<< orphan*/  QLCNIC_FW_HANG ; 
 int /*<<< orphan*/  QLC_DEV_CLR_REF_CNT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_DEV_CLR_RST_QSCNT (int,int /*<<< orphan*/ ) ; 
 int QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  __QLCNIC_START_FW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qlcnic_api_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_api_unlock (struct qlcnic_adapter*) ; 

void qlcnic_clr_all_drv_state(struct qlcnic_adapter *adapter, u8 failed)
{
	u32  val;

	if (qlcnic_api_lock(adapter))
		goto err;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_ACTIVE);
	QLC_DEV_CLR_REF_CNT(val, adapter->portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_ACTIVE, val);

	if (failed) {
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_FAILED);
		dev_info(&adapter->pdev->dev,
				"Device state set to Failed. Please Reboot\n");
	} else if (!(val & 0x11111111))
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_COLD);

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	QLC_DEV_CLR_RST_QSCNT(val, adapter->portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	qlcnic_api_unlock(adapter);
err:
	adapter->fw_fail_cnt = 0;
	adapter->flags &= ~QLCNIC_FW_HANG;
	clear_bit(__QLCNIC_START_FW, &adapter->state);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
}