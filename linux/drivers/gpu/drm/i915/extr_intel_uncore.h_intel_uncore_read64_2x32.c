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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct intel_uncore {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 scalar_t__ intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64
intel_uncore_read64_2x32(struct intel_uncore *uncore,
			 i915_reg_t lower_reg, i915_reg_t upper_reg)
{
	u32 upper, lower, old_upper, loop = 0;
	upper = intel_uncore_read(uncore, upper_reg);
	do {
		old_upper = upper;
		lower = intel_uncore_read(uncore, lower_reg);
		upper = intel_uncore_read(uncore, upper_reg);
	} while (upper != old_upper && loop++ < 2);
	return (u64)upper << 32 | lower;
}