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
struct pci_dn {int dummy; } ;
struct eeh_dev {TYPE_1__* pe; scalar_t__ physfn; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int EEH_PE_CFG_BLOCKED ; 
 int EEH_PE_RESET ; 
 struct eeh_dev* pdn_to_eeh_dev (struct pci_dn*) ; 

__attribute__((used)) static inline bool pnv_eeh_cfg_blocked(struct pci_dn *pdn)
{
	struct eeh_dev *edev = pdn_to_eeh_dev(pdn);

	if (!edev || !edev->pe)
		return false;

	/*
	 * We will issue FLR or AF FLR to all VFs, which are contained
	 * in VF PE. It relies on the EEH PCI config accessors. So we
	 * can't block them during the window.
	 */
	if (edev->physfn && (edev->pe->state & EEH_PE_RESET))
		return false;

	if (edev->pe->state & EEH_PE_CFG_BLOCKED)
		return true;

	return false;
}