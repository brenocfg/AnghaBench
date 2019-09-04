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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 

__attribute__((used)) static int octeon_dummy_write_config(struct pci_bus *bus, unsigned int devfn,
				     int reg, int size, u32 val)
{
	return PCIBIOS_FUNC_NOT_SUPPORTED;
}