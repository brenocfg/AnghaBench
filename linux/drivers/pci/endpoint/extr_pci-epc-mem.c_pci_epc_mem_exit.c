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
struct pci_epc_mem {struct pci_epc_mem* bitmap; } ;
struct pci_epc {struct pci_epc_mem* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pci_epc_mem*) ; 

void pci_epc_mem_exit(struct pci_epc *epc)
{
	struct pci_epc_mem *mem = epc->mem;

	epc->mem = NULL;
	kfree(mem->bitmap);
	kfree(mem);
}