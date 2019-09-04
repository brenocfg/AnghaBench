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
struct rt3883_pci_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT3883_PCI_REG_CFGADDR ; 
 int /*<<< orphan*/  RT3883_PCI_REG_CFGDATA ; 
 int /*<<< orphan*/  rt3883_pci_get_cfgaddr (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rt3883_pci_w32 (struct rt3883_pci_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt3883_pci_write_cfg32(struct rt3883_pci_controller *rpc,
				 unsigned bus, unsigned slot,
				 unsigned func, unsigned reg, u32 val)
{
	unsigned long flags;
	u32 address;

	address = rt3883_pci_get_cfgaddr(bus, slot, func, reg);

	rt3883_pci_w32(rpc, address, RT3883_PCI_REG_CFGADDR);
	rt3883_pci_w32(rpc, val, RT3883_PCI_REG_CFGDATA);
}