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
typedef  int u32 ;
struct drm_i915_reg_descriptor {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct drm_i915_reg_descriptor *
__find_reg(const struct drm_i915_reg_descriptor *table, int count, u32 addr)
{
	int start = 0, end = count;
	while (start < end) {
		int mid = start + (end - start) / 2;
		int ret = addr - i915_mmio_reg_offset(table[mid].addr);
		if (ret < 0)
			end = mid;
		else if (ret > 0)
			start = mid + 1;
		else
			return &table[mid];
	}
	return NULL;
}