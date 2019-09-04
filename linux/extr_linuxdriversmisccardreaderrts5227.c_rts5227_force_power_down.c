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
 scalar_t__ AUTOLOAD_CFG_BASE ; 
 scalar_t__ FPDCTL ; 
 scalar_t__ HOST_ENTER_S3 ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,scalar_t__,int,int) ; 

__attribute__((used)) static void rts5227_force_power_down(struct rtsx_pcr *pcr, u8 pm_state)
{
	/* Set relink_time to 0 */
	rtsx_pci_write_register(pcr, AUTOLOAD_CFG_BASE + 1, 0xFF, 0);
	rtsx_pci_write_register(pcr, AUTOLOAD_CFG_BASE + 2, 0xFF, 0);
	rtsx_pci_write_register(pcr, AUTOLOAD_CFG_BASE + 3, 0x01, 0);

	if (pm_state == HOST_ENTER_S3)
		rtsx_pci_write_register(pcr, pcr->reg_pm_ctrl3, 0x10, 0x10);

	rtsx_pci_write_register(pcr, FPDCTL, 0x03, 0x03);
}