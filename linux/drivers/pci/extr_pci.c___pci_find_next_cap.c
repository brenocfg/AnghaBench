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
typedef  int /*<<< orphan*/  u8 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCI_FIND_CAP_TTL ; 
 int __pci_find_next_cap_ttl (struct pci_bus*,unsigned int,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int __pci_find_next_cap(struct pci_bus *bus, unsigned int devfn,
			       u8 pos, int cap)
{
	int ttl = PCI_FIND_CAP_TTL;

	return __pci_find_next_cap_ttl(bus, devfn, pos, cap, &ttl);
}