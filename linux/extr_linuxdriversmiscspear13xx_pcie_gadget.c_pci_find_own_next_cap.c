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
typedef  int /*<<< orphan*/  u32 ;
struct spear_pcie_gadget_config {int dummy; } ;

/* Variables and functions */
 int PCI_FIND_CAP_TTL ; 
 int pci_find_own_next_cap_ttl (struct spear_pcie_gadget_config*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int pci_find_own_next_cap(struct spear_pcie_gadget_config *config,
			u32 pos, int cap)
{
	int ttl = PCI_FIND_CAP_TTL;

	return pci_find_own_next_cap_ttl(config, pos, cap, &ttl);
}