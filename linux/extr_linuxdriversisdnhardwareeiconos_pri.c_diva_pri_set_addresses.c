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
struct TYPE_7__ {int* mem_type_id; int /*<<< orphan*/ * addr; int /*<<< orphan*/ * bar; } ;
struct TYPE_8__ {TYPE_2__ pci; } ;
struct TYPE_6__ {int /*<<< orphan*/  prom; int /*<<< orphan*/  sdram_bar; int /*<<< orphan*/  cfg; int /*<<< orphan*/  reset; int /*<<< orphan*/  ram; int /*<<< orphan*/  Config; int /*<<< orphan*/  Control; int /*<<< orphan*/  Address; } ;
struct TYPE_9__ {TYPE_3__ resources; TYPE_1__ xdi_adapter; } ;
typedef  TYPE_4__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 size_t MEM_TYPE_ADDRESS ; 
 size_t MEM_TYPE_CFG ; 
 size_t MEM_TYPE_CONFIG ; 
 size_t MEM_TYPE_CONTROL ; 
 size_t MEM_TYPE_PROM ; 
 size_t MEM_TYPE_RAM ; 
 size_t MEM_TYPE_RESET ; 
 scalar_t__ MP_IRQ_RESET ; 
 scalar_t__ MP_RESET ; 
 scalar_t__ MP_SHARED_RAM_OFFSET ; 

__attribute__((used)) static void diva_pri_set_addresses(diva_os_xdi_adapter_t *a)
{
	a->resources.pci.mem_type_id[MEM_TYPE_ADDRESS] = 0;
	a->resources.pci.mem_type_id[MEM_TYPE_CONTROL] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_CONFIG] = 4;
	a->resources.pci.mem_type_id[MEM_TYPE_RAM] = 0;
	a->resources.pci.mem_type_id[MEM_TYPE_RESET] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_CFG] = 4;
	a->resources.pci.mem_type_id[MEM_TYPE_PROM] = 3;

	a->xdi_adapter.Address = a->resources.pci.addr[0];
	a->xdi_adapter.Control = a->resources.pci.addr[2];
	a->xdi_adapter.Config = a->resources.pci.addr[4];

	a->xdi_adapter.ram = a->resources.pci.addr[0];
	a->xdi_adapter.ram += MP_SHARED_RAM_OFFSET;

	a->xdi_adapter.reset = a->resources.pci.addr[2];
	a->xdi_adapter.reset += MP_RESET;

	a->xdi_adapter.cfg = a->resources.pci.addr[4];
	a->xdi_adapter.cfg += MP_IRQ_RESET;

	a->xdi_adapter.sdram_bar = a->resources.pci.bar[0];

	a->xdi_adapter.prom = a->resources.pci.addr[3];
}