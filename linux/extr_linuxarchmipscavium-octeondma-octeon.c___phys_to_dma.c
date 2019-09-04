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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */

dma_addr_t __phys_to_dma(struct device *dev, phys_addr_t paddr)
{
#ifdef CONFIG_PCI
	if (dev && dev_is_pci(dev))
		return octeon_pci_dma_ops->phys_to_dma(dev, paddr);
#endif
	return paddr;
}