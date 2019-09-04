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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_4__ {scalar_t__ curr_state; } ;
struct TYPE_5__ {TYPE_1__ idc; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QLCRDX (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWRX (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  QLC_83XX_IDC_CTRL ; 
 scalar_t__ QLC_83XX_IDC_DEV_COLD ; 
 int /*<<< orphan*/  QLC_83XX_IDC_DEV_STATE ; 
 scalar_t__ QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY ; 
 int /*<<< orphan*/  QLC_83XX_RECOVER_DRV_LOCK ; 
 scalar_t__ qlcnic_83xx_idc_check_state_validity (struct qlcnic_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_cold_state_handler (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_idc_update_major_version (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_83xx_lock_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_unlock_driver (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_auto_fw_reset ; 
 scalar_t__ qlcnic_load_fw_file ; 

__attribute__((used)) static int
qlcnic_83xx_idc_first_to_load_function_handler(struct qlcnic_adapter *adapter)
{
	u32 state, val;

	if (qlcnic_83xx_lock_driver(adapter))
		return -EIO;

	/* Clear driver lock register */
	QLCWRX(adapter->ahw, QLC_83XX_RECOVER_DRV_LOCK, 0);
	if (qlcnic_83xx_idc_update_major_version(adapter, 0)) {
		qlcnic_83xx_unlock_driver(adapter);
		return -EIO;
	}

	state =	QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_STATE);
	if (qlcnic_83xx_idc_check_state_validity(adapter, state)) {
		qlcnic_83xx_unlock_driver(adapter);
		return -EIO;
	}

	if (state != QLC_83XX_IDC_DEV_COLD && qlcnic_load_fw_file) {
		QLCWRX(adapter->ahw, QLC_83XX_IDC_DEV_STATE,
		       QLC_83XX_IDC_DEV_COLD);
		state = QLC_83XX_IDC_DEV_COLD;
	}

	adapter->ahw->idc.curr_state = state;
	/* First to load function should cold boot the device */
	if (state == QLC_83XX_IDC_DEV_COLD)
		qlcnic_83xx_idc_cold_state_handler(adapter);

	/* Check if reset recovery is enabled */
	if (qlcnic_auto_fw_reset) {
		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		val = val & ~QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY;
		QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);
	}

	qlcnic_83xx_unlock_driver(adapter);

	return 0;
}