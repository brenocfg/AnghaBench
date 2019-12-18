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
typedef  int u8 ;
typedef  int u32 ;
struct qlcnic_adapter {int dev_init_timeo; int portnum; TYPE_1__* pdev; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  QLCDB (struct qlcnic_adapter*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  QLCNIC_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_ACTIVE ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_IDC_VER ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_STATE ; 
#define  QLCNIC_DEV_COLD 134 
#define  QLCNIC_DEV_FAILED 133 
#define  QLCNIC_DEV_INITIALIZING 132 
#define  QLCNIC_DEV_NEED_QUISCENT 131 
#define  QLCNIC_DEV_NEED_RESET 130 
#define  QLCNIC_DEV_QUISCENT 129 
#define  QLCNIC_DEV_READY 128 
 int QLCNIC_DRV_IDC_VER ; 
 int /*<<< orphan*/  QLC_DEV_CLR_RST_QSCNT (int,int) ; 
 int /*<<< orphan*/  QLC_DEV_SET_QSCNT_RDY (int,int) ; 
 int /*<<< orphan*/  QLC_DEV_SET_REF_CNT (int,int) ; 
 int /*<<< orphan*/  QLC_DEV_SET_RST_RDY (int,int) ; 
 int QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __QLCNIC_START_FW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ qlcnic_api_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_api_unlock (struct qlcnic_adapter*) ; 
 int qlcnic_check_idc_ver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_idc_debug_info (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlcnic_can_start_firmware(struct qlcnic_adapter *adapter)
{
	u32 val, prev_state;
	u8 dev_init_timeo = adapter->dev_init_timeo;
	u8 portnum = adapter->portnum;
	u8 ret;

	if (test_and_clear_bit(__QLCNIC_START_FW, &adapter->state))
		return 1;

	if (qlcnic_api_lock(adapter))
		return -1;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_ACTIVE);
	if (!(val & (1 << (portnum * 4)))) {
		QLC_DEV_SET_REF_CNT(val, portnum);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_ACTIVE, val);
	}

	prev_state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	QLCDB(adapter, HW, "Device state = %u\n", prev_state);

	switch (prev_state) {
	case QLCNIC_DEV_COLD:
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_INITIALIZING);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_IDC_VER,
				    QLCNIC_DRV_IDC_VER);
		qlcnic_idc_debug_info(adapter, 0);
		qlcnic_api_unlock(adapter);
		return 1;

	case QLCNIC_DEV_READY:
		ret = qlcnic_check_idc_ver(adapter);
		qlcnic_api_unlock(adapter);
		return ret;

	case QLCNIC_DEV_NEED_RESET:
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
		QLC_DEV_SET_RST_RDY(val, portnum);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);
		break;

	case QLCNIC_DEV_NEED_QUISCENT:
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
		QLC_DEV_SET_QSCNT_RDY(val, portnum);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);
		break;

	case QLCNIC_DEV_FAILED:
		dev_err(&adapter->pdev->dev, "Device in failed state.\n");
		qlcnic_api_unlock(adapter);
		return -1;

	case QLCNIC_DEV_INITIALIZING:
	case QLCNIC_DEV_QUISCENT:
		break;
	}

	qlcnic_api_unlock(adapter);

	do {
		msleep(1000);
		prev_state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);

		if (prev_state == QLCNIC_DEV_QUISCENT)
			continue;
	} while ((prev_state != QLCNIC_DEV_READY) && --dev_init_timeo);

	if (!dev_init_timeo) {
		dev_err(&adapter->pdev->dev,
			"Waiting for device to initialize timeout\n");
		return -1;
	}

	if (qlcnic_api_lock(adapter))
		return -1;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	QLC_DEV_CLR_RST_QSCNT(val, portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	ret = qlcnic_check_idc_ver(adapter);
	qlcnic_api_unlock(adapter);

	return ret;
}