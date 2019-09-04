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
struct pci_root_info {int node; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 struct pci_root_info* x86_find_pci_root_info (int) ; 

int x86_pci_root_bus_node(int bus)
{
	struct pci_root_info *info = x86_find_pci_root_info(bus);

	if (!info)
		return NUMA_NO_NODE;

	return info->node;
}