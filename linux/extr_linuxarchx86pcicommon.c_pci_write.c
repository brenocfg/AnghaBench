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
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int raw_pci_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_write(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 value)
{
	return raw_pci_write(pci_domain_nr(bus), bus->number,
				  devfn, where, size, value);
}