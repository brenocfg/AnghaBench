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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  __dma_sync (struct device*,int /*<<< orphan*/ ,size_t,int) ; 

void arch_sync_dma_for_device(struct device *dev, phys_addr_t paddr,
		size_t size, enum dma_data_direction dir)
{
	__dma_sync(dev, paddr, size, dir);
}