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
typedef  unsigned int u64 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 scalar_t__ HAS_PAGE_SIZES (struct drm_i915_private*,unsigned int) ; 
 unsigned int* page_sizes ; 

__attribute__((used)) static unsigned int get_largest_page_size(struct drm_i915_private *i915,
					  u64 rem)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(page_sizes); ++i) {
		unsigned int page_size = page_sizes[i];

		if (HAS_PAGE_SIZES(i915, page_size) && rem >= page_size)
			return page_size;
	}

	return 0;
}