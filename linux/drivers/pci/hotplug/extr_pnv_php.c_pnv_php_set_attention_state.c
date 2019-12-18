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
typedef  int /*<<< orphan*/  u16 ;
struct pnv_php_slot {scalar_t__ attention_state; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_SLTCTL ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_AIC ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_ATTN_IND_OFF ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_ATTN_IND_ON ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pnv_php_slot* to_pnv_php_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int pnv_php_set_attention_state(struct hotplug_slot *slot, u8 state)
{
	struct pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	struct pci_dev *bridge = php_slot->pdev;
	u16 new, mask;

	php_slot->attention_state = state;
	if (!bridge)
		return 0;

	mask = PCI_EXP_SLTCTL_AIC;

	if (state)
		new = PCI_EXP_SLTCTL_ATTN_IND_ON;
	else
		new = PCI_EXP_SLTCTL_ATTN_IND_OFF;

	pcie_capability_clear_and_set_word(bridge, PCI_EXP_SLTCTL, mask, new);

	return 0;
}