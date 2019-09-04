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
struct rtsx_pcr {int /*<<< orphan*/  aspm_en; scalar_t__ pcie_cap; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  rtsx_pci_update_cfg_byte (struct rtsx_pcr*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rtsx_pci_enable_aspm(struct rtsx_pcr *pcr)
{
	rtsx_pci_update_cfg_byte(pcr, pcr->pcie_cap + PCI_EXP_LNKCTL,
		0xFC, pcr->aspm_en);
}