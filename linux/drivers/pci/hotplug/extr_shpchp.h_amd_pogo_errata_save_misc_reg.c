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
typedef  int /*<<< orphan*/  u32 ;
struct slot {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  pcix_misc2_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIX_MISCII_OFFSET ; 
 int /*<<< orphan*/  PERRFATALENABLE_MASK ; 
 int /*<<< orphan*/  PERRFLOODENABLE_MASK ; 
 int /*<<< orphan*/  PERRNONFATALENABLE_MASK ; 
 int /*<<< orphan*/  SERRFATALENABLE_MASK ; 
 int /*<<< orphan*/  SERRNONFATALENABLE_MASK ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void amd_pogo_errata_save_misc_reg(struct slot *p_slot)
{
	u32 pcix_misc2_temp;

	/* save MiscII register */
	pci_read_config_dword(p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, &pcix_misc2_temp);

	p_slot->ctrl->pcix_misc2_reg = pcix_misc2_temp;

	/* clear SERR/PERR enable bits */
	pcix_misc2_temp &= ~SERRFATALENABLE_MASK;
	pcix_misc2_temp &= ~SERRNONFATALENABLE_MASK;
	pcix_misc2_temp &= ~PERRFLOODENABLE_MASK;
	pcix_misc2_temp &= ~PERRFATALENABLE_MASK;
	pcix_misc2_temp &= ~PERRNONFATALENABLE_MASK;
	pci_write_config_dword(p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, pcix_misc2_temp);
}