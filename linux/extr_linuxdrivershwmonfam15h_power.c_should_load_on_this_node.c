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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_NORTHBRIDGE_CAP ; 
 int /*<<< orphan*/  pci_bus_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool should_load_on_this_node(struct pci_dev *f4)
{
	u32 val;

	pci_bus_read_config_dword(f4->bus, PCI_DEVFN(PCI_SLOT(f4->devfn), 3),
				  REG_NORTHBRIDGE_CAP, &val);
	if ((val & BIT(29)) && ((val >> 30) & 3))
		return false;

	return true;
}