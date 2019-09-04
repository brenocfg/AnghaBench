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
typedef  int u8 ;
struct rtsx_cr_option {scalar_t__ dev_aspm_mode; } ;
struct rtsx_pcr {int aspm_enabled; int aspm_en; scalar_t__ pcie_cap; struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_FORCE_CTL ; 
 int /*<<< orphan*/  ASPM_MASK_NEG ; 
 scalar_t__ DEV_ASPM_BACKDOOR ; 
 scalar_t__ DEV_ASPM_DYNAMIC ; 
 int FORCE_ASPM_CTL0 ; 
 int FORCE_ASPM_VAL_MASK ; 
 scalar_t__ PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  rtsx_pci_update_cfg_byte (struct rtsx_pcr*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rts5260_set_aspm(struct rtsx_pcr *pcr, bool enable)
{
	struct rtsx_cr_option *option = &pcr->option;
	u8 val = 0;

	if (pcr->aspm_enabled == enable)
		return;

	if (option->dev_aspm_mode == DEV_ASPM_DYNAMIC) {
		if (enable)
			val = pcr->aspm_en;
		rtsx_pci_update_cfg_byte(pcr, pcr->pcie_cap + PCI_EXP_LNKCTL,
					 ASPM_MASK_NEG, val);
	} else if (option->dev_aspm_mode == DEV_ASPM_BACKDOOR) {
		u8 mask = FORCE_ASPM_VAL_MASK | FORCE_ASPM_CTL0;

		if (!enable)
			val = FORCE_ASPM_CTL0;
		rtsx_pci_write_register(pcr, ASPM_FORCE_CTL, mask, val);
	}

	pcr->aspm_enabled = enable;
}