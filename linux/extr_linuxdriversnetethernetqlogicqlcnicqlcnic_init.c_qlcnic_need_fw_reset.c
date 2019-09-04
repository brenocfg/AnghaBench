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
struct qlcnic_adapter {int flags; scalar_t__ fw; scalar_t__ need_fw_reset; } ;

/* Variables and functions */
 int QLCNIC_FW_HANG ; 
 scalar_t__ qlcnic_check_fw_hearbeat (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_rom_lock_recovery (struct qlcnic_adapter*) ; 

int
qlcnic_need_fw_reset(struct qlcnic_adapter *adapter)
{
	if ((adapter->flags & QLCNIC_FW_HANG) ||
			qlcnic_check_fw_hearbeat(adapter)) {
		qlcnic_rom_lock_recovery(adapter);
		return 1;
	}

	if (adapter->need_fw_reset)
		return 1;

	if (adapter->fw)
		return 1;

	return 0;
}