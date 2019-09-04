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
struct pci_bus {int dummy; } ;
struct TYPE_2__ {int bs_legacy_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* SN_PCIBUS_BUSSOFT (struct pci_bus*) ; 
 int __IA64_UNCACHED_OFFSET ; 

char *sn_pci_get_legacy_mem(struct pci_bus *bus)
{
	if (!SN_PCIBUS_BUSSOFT(bus))
		return ERR_PTR(-ENODEV);

	return (char *)(SN_PCIBUS_BUSSOFT(bus)->bs_legacy_mem | __IA64_UNCACHED_OFFSET);
}