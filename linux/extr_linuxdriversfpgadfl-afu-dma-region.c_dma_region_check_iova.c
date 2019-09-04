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
typedef  scalar_t__ u64 ;
struct dfl_afu_dma_region {scalar_t__ iova; scalar_t__ length; } ;

/* Variables and functions */

__attribute__((used)) static bool dma_region_check_iova(struct dfl_afu_dma_region *region,
				  u64 iova, u64 size)
{
	if (!size && region->iova != iova)
		return false;

	return (region->iova <= iova) &&
		(region->length + region->iova >= iova + size);
}