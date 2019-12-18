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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct pci_cap_saved_state {TYPE_1__ cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXT_CAP_ID_LTR ; 
 scalar_t__ PCI_LTR_MAX_NOSNOOP_LAT ; 
 scalar_t__ PCI_LTR_MAX_SNOOP_LAT ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_cap_saved_state* pci_find_saved_ext_cap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_restore_ltr_state(struct pci_dev *dev)
{
	struct pci_cap_saved_state *save_state;
	int ltr;
	u16 *cap;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_LTR);
	ltr = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_LTR);
	if (!save_state || !ltr)
		return;

	cap = (u16 *)&save_state->cap.data[0];
	pci_write_config_word(dev, ltr + PCI_LTR_MAX_SNOOP_LAT, *cap++);
	pci_write_config_word(dev, ltr + PCI_LTR_MAX_NOSNOOP_LAT, *cap++);
}