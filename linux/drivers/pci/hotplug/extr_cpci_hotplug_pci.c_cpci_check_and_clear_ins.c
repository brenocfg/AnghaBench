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
typedef  int u16 ;
struct slot {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int HS_CSR_INS ; 
 int /*<<< orphan*/  PCI_CAP_ID_CHSWP ; 
 int pci_bus_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_bus_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ pci_bus_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int cpci_check_and_clear_ins(struct slot *slot)
{
	int hs_cap;
	u16 hs_csr;
	int ins = 0;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		return 0;
	if (pci_bus_read_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		return 0;
	if (hs_csr & HS_CSR_INS) {
		/* Clear INS (by setting it) */
		if (pci_bus_write_config_word(slot->bus,
					      slot->devfn,
					      hs_cap + 2,
					      hs_csr))
			ins = 0;
		else
			ins = 1;
	}
	return ins;
}