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
struct pci_host_bridge {int /*<<< orphan*/  dma_ranges; int /*<<< orphan*/  windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pci_host_bridge*) ; 
 int /*<<< orphan*/  pci_free_resource_list (int /*<<< orphan*/ *) ; 

void pci_free_host_bridge(struct pci_host_bridge *bridge)
{
	pci_free_resource_list(&bridge->windows);
	pci_free_resource_list(&bridge->dma_ranges);

	kfree(bridge);
}