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
struct pci_mmcfg_region {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 struct pci_mmcfg_region* pci_mmconfig_lookup (unsigned int,int) ; 

__attribute__((used)) static u32 get_base_addr(unsigned int seg, int bus, unsigned devfn)
{
	struct pci_mmcfg_region *cfg = pci_mmconfig_lookup(seg, bus);

	if (cfg)
		return cfg->address;
	return 0;
}