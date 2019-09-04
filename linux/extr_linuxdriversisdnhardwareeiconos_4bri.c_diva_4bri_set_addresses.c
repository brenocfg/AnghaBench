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
typedef  int dword ;
struct TYPE_8__ {int ControllerNumber; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * prom; int /*<<< orphan*/ * ctlReg; int /*<<< orphan*/ * ram; int /*<<< orphan*/ * Control; int /*<<< orphan*/ * Address; } ;
struct TYPE_6__ {int qoffset; int* mem_type_id; int /*<<< orphan*/ ** addr; } ;
struct TYPE_7__ {TYPE_1__ pci; } ;
struct TYPE_9__ {TYPE_3__ xdi_adapter; TYPE_2__ resources; } ;
typedef  TYPE_4__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 size_t MEM_TYPE_ADDRESS ; 
 size_t MEM_TYPE_CONTROL ; 
 size_t MEM_TYPE_CTLREG ; 
 size_t MEM_TYPE_PROM ; 
 size_t MEM_TYPE_RAM ; 
 size_t MEM_TYPE_RESET ; 
 int MQ_SHARED_RAM_SIZE ; 

__attribute__((used)) static void diva_4bri_set_addresses(diva_os_xdi_adapter_t *a)
{
	dword offset = a->resources.pci.qoffset;
	dword c_offset = offset * a->xdi_adapter.ControllerNumber;

	a->resources.pci.mem_type_id[MEM_TYPE_RAM] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_ADDRESS] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_CONTROL] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_RESET] = 0;
	a->resources.pci.mem_type_id[MEM_TYPE_CTLREG] = 3;
	a->resources.pci.mem_type_id[MEM_TYPE_PROM] = 0;

	/*
	  Set up hardware related pointers
	*/
	a->xdi_adapter.Address = a->resources.pci.addr[2];	/* BAR2 SDRAM  */
	a->xdi_adapter.Address += c_offset;

	a->xdi_adapter.Control = a->resources.pci.addr[2];	/* BAR2 SDRAM  */

	a->xdi_adapter.ram = a->resources.pci.addr[2];	/* BAR2 SDRAM  */
	a->xdi_adapter.ram += c_offset + (offset - MQ_SHARED_RAM_SIZE);

	a->xdi_adapter.reset = a->resources.pci.addr[0];	/* BAR0 CONFIG */
	/*
	  ctlReg contains the register address for the MIPS CPU reset control
	*/
	a->xdi_adapter.ctlReg = a->resources.pci.addr[3];	/* BAR3 CNTRL  */
	/*
	  prom contains the register address for FPGA and EEPROM programming
	*/
	a->xdi_adapter.prom = &a->xdi_adapter.reset[0x6E];
}