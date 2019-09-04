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
struct pci_bus {int /*<<< orphan*/  sysdata; } ;
struct cns3xxx_pcie {int dummy; } ;

/* Variables and functions */
 struct cns3xxx_pcie* sysdata_to_cnspci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cns3xxx_pcie *pbus_to_cnspci(struct pci_bus *bus)
{
	return sysdata_to_cnspci(bus->sysdata);
}