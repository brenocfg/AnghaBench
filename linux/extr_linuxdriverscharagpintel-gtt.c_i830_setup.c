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
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {scalar_t__ gtt_phys_addr; int /*<<< orphan*/  registers; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I810_MMADR_BAR ; 
 scalar_t__ I810_PTE_BASE ; 
 int /*<<< orphan*/  KB (int) ; 
 TYPE_1__ intel_private ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i830_setup(void)
{
	phys_addr_t reg_addr;

	reg_addr = pci_resource_start(intel_private.pcidev, I810_MMADR_BAR);

	intel_private.registers = ioremap(reg_addr, KB(64));
	if (!intel_private.registers)
		return -ENOMEM;

	intel_private.gtt_phys_addr = reg_addr + I810_PTE_BASE;

	return 0;
}