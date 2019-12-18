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
typedef  int /*<<< orphan*/  u16 ;
struct slot {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS_CSR_LOO ; 
 int /*<<< orphan*/  PCI_CAP_ID_CHSWP ; 
 int pci_bus_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_bus_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_bus_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int cpci_set_attention_status(struct slot *slot, int status)
{
	int hs_cap;
	u16 hs_csr;

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
	if (status)
		hs_csr |= HS_CSR_LOO;
	else
		hs_csr &= ~HS_CSR_LOO;
	if (pci_bus_write_config_word(slot->bus,
				      slot->devfn,
				      hs_cap + 2,
				      hs_csr))
		return 0;
	return 1;
}