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

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 unsigned int SCATTERLIST_MAX_SEGMENT ; 
 unsigned int rounddown (unsigned int,unsigned int) ; 
 unsigned int swiotlb_max_segment () ; 

__attribute__((used)) static inline unsigned int i915_sg_segment_size(void)
{
	unsigned int size = swiotlb_max_segment();

	if (size == 0)
		return SCATTERLIST_MAX_SEGMENT;

	size = rounddown(size, PAGE_SIZE);
	/* swiotlb_max_segment_size can return 1 byte when it means one page. */
	if (size < PAGE_SIZE)
		size = PAGE_SIZE;

	return size;
}