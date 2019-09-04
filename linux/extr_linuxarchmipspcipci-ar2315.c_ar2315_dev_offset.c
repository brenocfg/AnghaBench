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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR2315_PCI_HOST_SDRAM_BASEADDR ; 
 scalar_t__ dev_is_pci (struct device*) ; 

__attribute__((used)) static inline dma_addr_t ar2315_dev_offset(struct device *dev)
{
	if (dev && dev_is_pci(dev))
		return AR2315_PCI_HOST_SDRAM_BASEADDR;
	return 0;
}