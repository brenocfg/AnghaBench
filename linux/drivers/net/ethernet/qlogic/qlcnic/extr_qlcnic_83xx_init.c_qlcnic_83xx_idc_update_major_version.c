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
typedef  int u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int EBUSY ; 
 int QLCRDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWRX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int QLC_83XX_IDC_MAJOR_VERSION ; 
 int /*<<< orphan*/  QLC_83XX_IDC_MAJ_VERSION ; 
 scalar_t__ qlcnic_83xx_lock_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_unlock_driver (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_83xx_idc_update_major_version(struct qlcnic_adapter *adapter,
						int lock)
{
	u32 val;

	if (lock) {
		if (qlcnic_83xx_lock_driver(adapter))
			return -EBUSY;
	}

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_MAJ_VERSION);
	val = val & ~0xFF;
	val = val | QLC_83XX_IDC_MAJOR_VERSION;
	QLCWRX(adapter->ahw, QLC_83XX_IDC_MAJ_VERSION, val);

	if (lock)
		qlcnic_83xx_unlock_driver(adapter);

	return 0;
}