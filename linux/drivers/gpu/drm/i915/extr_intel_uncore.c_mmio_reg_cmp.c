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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 scalar_t__ i915_mmio_reg_offset (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int mmio_reg_cmp(u32 key, const i915_reg_t *reg)
{
	u32 offset = i915_mmio_reg_offset(*reg);

	if (key < offset)
		return -1;
	else if (key > offset)
		return 1;
	else
		return 0;
}