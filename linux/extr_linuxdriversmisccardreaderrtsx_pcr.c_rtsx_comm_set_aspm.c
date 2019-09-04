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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_cr_option {scalar_t__ dev_aspm_mode; } ;
struct rtsx_pcr {int aspm_enabled; int /*<<< orphan*/  aspm_en; struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_FORCE_CTL ; 
 scalar_t__ DEV_ASPM_BACKDOOR ; 
 scalar_t__ DEV_ASPM_DYNAMIC ; 
 int /*<<< orphan*/  FORCE_ASPM_VAL_MASK ; 
 int /*<<< orphan*/  rtsx_pci_disable_aspm (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_enable_aspm (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsx_comm_set_aspm(struct rtsx_pcr *pcr, bool enable)
{
	struct rtsx_cr_option *option = &pcr->option;

	if (pcr->aspm_enabled == enable)
		return;

	if (option->dev_aspm_mode == DEV_ASPM_DYNAMIC) {
		if (enable)
			rtsx_pci_enable_aspm(pcr);
		else
			rtsx_pci_disable_aspm(pcr);
	} else if (option->dev_aspm_mode == DEV_ASPM_BACKDOOR) {
		u8 mask = FORCE_ASPM_VAL_MASK;
		u8 val = 0;

		if (enable)
			val = pcr->aspm_en;
		rtsx_pci_write_register(pcr, ASPM_FORCE_CTL,  mask, val);
	}

	pcr->aspm_enabled = enable;
}