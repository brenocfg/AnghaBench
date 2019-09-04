#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ram; int cfg; int Address; int reset; int port; int ctlReg; } ;
struct TYPE_6__ {int* mem_type_id; int* addr; } ;
struct TYPE_7__ {TYPE_1__ pci; } ;
struct TYPE_9__ {TYPE_3__ xdi_adapter; TYPE_2__ resources; } ;
typedef  TYPE_4__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 size_t MEM_TYPE_ADDRESS ; 
 size_t MEM_TYPE_CFG ; 
 size_t MEM_TYPE_CTLREG ; 
 size_t MEM_TYPE_PORT ; 
 size_t MEM_TYPE_RAM ; 
 size_t MEM_TYPE_RESET ; 
 int M_PCI_RESET ; 

__attribute__((used)) static void diva_bri_set_addresses(diva_os_xdi_adapter_t *a)
{
	a->resources.pci.mem_type_id[MEM_TYPE_RAM] = 0;
	a->resources.pci.mem_type_id[MEM_TYPE_CFG] = 1;
	a->resources.pci.mem_type_id[MEM_TYPE_ADDRESS] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_RESET] = 1;
	a->resources.pci.mem_type_id[MEM_TYPE_PORT] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_CTLREG] = 2;

	a->xdi_adapter.ram = a->resources.pci.addr[0];
	a->xdi_adapter.cfg = a->resources.pci.addr[1];
	a->xdi_adapter.Address = a->resources.pci.addr[2];

	a->xdi_adapter.reset = a->xdi_adapter.cfg;
	a->xdi_adapter.port = a->xdi_adapter.Address;

	a->xdi_adapter.ctlReg = a->xdi_adapter.port + M_PCI_RESET;

	a->xdi_adapter.reset += 0x4C;	/* PLX 9050 !! */
}