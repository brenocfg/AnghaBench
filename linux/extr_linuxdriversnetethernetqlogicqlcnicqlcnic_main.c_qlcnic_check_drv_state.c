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
struct qlcnic_hardware_context {int pci_func; } ;
struct qlcnic_adapter {int flags; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CRB_DRV_ACTIVE ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_STATE ; 
 int QLCNIC_FW_RESET_OWNER ; 
 int QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_check_drv_state(struct qlcnic_adapter *adapter)
{
	int act, state, active_mask;
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	act = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_ACTIVE);

	if (adapter->flags & QLCNIC_FW_RESET_OWNER) {
		active_mask = (~(1 << (ahw->pci_func * 4)));
		act = act & active_mask;
	}

	if (((state & 0x11111111) == (act & 0x11111111)) ||
			((act & 0x11111111) == ((state >> 1) & 0x11111111)))
		return 0;
	else
		return 1;
}