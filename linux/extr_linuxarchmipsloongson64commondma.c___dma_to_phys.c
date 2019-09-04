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
typedef  int phys_addr_t ;
typedef  int dma_addr_t ;

/* Variables and functions */

phys_addr_t __dma_to_phys(struct device *dev, dma_addr_t dma_addr)
{
#if defined(CONFIG_CPU_LOONGSON2F) && defined(CONFIG_64BIT)
	if (dma_addr > 0x8fffffff)
		return dma_addr;
	return dma_addr & 0x0fffffff;
#else
	return dma_addr & 0x7fffffff;
#endif
}