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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ max_direct_dma_addr; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int fls64 (scalar_t__) ; 
 scalar_t__ get_dma_offset (struct device*) ; 
 scalar_t__ memblock_end_of_DRAM () ; 

__attribute__((used)) static u64 swiotlb_powerpc_get_required(struct device *dev)
{
	u64 end, mask, max_direct_dma_addr = dev->archdata.max_direct_dma_addr;

	end = memblock_end_of_DRAM();
	if (max_direct_dma_addr && end > max_direct_dma_addr)
		end = max_direct_dma_addr;
	end += get_dma_offset(dev);

	mask = 1ULL << (fls64(end) - 1);
	mask += mask - 1;

	return mask;
}