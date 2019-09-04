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
struct pci_controller {int first_busno; int global_number; } ;
struct pci_bus {int number; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_token (char*) ; 

__attribute__((used)) static int rtas_write_config(struct pci_bus *bus, unsigned int devfn, int offset,
			     int len, u32 val)
{
	struct pci_controller *hose = pci_bus_to_host(bus);
	unsigned long addr = (offset & 0xff) | ((devfn & 0xff) << 8)
		| (((bus->number - hose->first_busno) & 0xff) << 16)
		| (hose->global_number << 24);
	int rval;

	rval = rtas_call(rtas_token("write-pci-config"), 3, 1, NULL,
			 addr, len, val);
	return rval? PCIBIOS_DEVICE_NOT_FOUND: PCIBIOS_SUCCESSFUL;
}