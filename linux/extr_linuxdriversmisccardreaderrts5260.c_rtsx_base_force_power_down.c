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
typedef  scalar_t__ u8 ;
struct rtsx_pcr {scalar_t__ reg_pm_ctrl3; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_POWER_DOWN ; 
 scalar_t__ AUTOLOAD_CFG_BASE ; 
 int /*<<< orphan*/  D3_DELINK_MODE_EN ; 
 scalar_t__ FPDCTL ; 
 scalar_t__ HOST_ENTER_S3 ; 
 int /*<<< orphan*/  MASK_8_BIT_DEF ; 
 int /*<<< orphan*/  RELINK_TIME_MASK ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsx_base_force_power_down(struct rtsx_pcr *pcr, u8 pm_state)
{
	/* Set relink_time to 0 */
	rtsx_pci_write_register(pcr, AUTOLOAD_CFG_BASE + 1, MASK_8_BIT_DEF, 0);
	rtsx_pci_write_register(pcr, AUTOLOAD_CFG_BASE + 2, MASK_8_BIT_DEF, 0);
	rtsx_pci_write_register(pcr, AUTOLOAD_CFG_BASE + 3,
				RELINK_TIME_MASK, 0);

	if (pm_state == HOST_ENTER_S3)
		rtsx_pci_write_register(pcr, pcr->reg_pm_ctrl3,
					D3_DELINK_MODE_EN, D3_DELINK_MODE_EN);

	rtsx_pci_write_register(pcr, FPDCTL, ALL_POWER_DOWN, ALL_POWER_DOWN);
}