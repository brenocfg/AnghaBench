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
struct TYPE_2__ {int /*<<< orphan*/  vnic_state; } ;
struct qlcnic_hardware_context {TYPE_1__ idc; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  QLCNIC_DEV_NPAR_NON_OPER ; 
 int /*<<< orphan*/  QLCWRX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_VNIC_STATE ; 
 scalar_t__ qlcnic_83xx_lock_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_unlock_driver (struct qlcnic_adapter*) ; 

int qlcnic_83xx_disable_vnic_mode(struct qlcnic_adapter *adapter, int lock)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	if (lock) {
		if (qlcnic_83xx_lock_driver(adapter))
			return -EBUSY;
	}

	QLCWRX(adapter->ahw, QLC_83XX_VNIC_STATE, QLCNIC_DEV_NPAR_NON_OPER);
	ahw->idc.vnic_state = QLCNIC_DEV_NPAR_NON_OPER;

	if (lock)
		qlcnic_83xx_unlock_driver(adapter);

	return 0;
}