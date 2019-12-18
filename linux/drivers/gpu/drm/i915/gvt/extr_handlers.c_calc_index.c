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
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 unsigned int INVALID_INDEX ; 
 unsigned int i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int calc_index(unsigned int offset, unsigned int start,
	unsigned int next, unsigned int end, i915_reg_t i915_end)
{
	unsigned int range = next - start;

	if (!end)
		end = i915_mmio_reg_offset(i915_end);
	if (offset < start || offset > end)
		return INVALID_INDEX;
	offset -= start;
	return offset / range;
}