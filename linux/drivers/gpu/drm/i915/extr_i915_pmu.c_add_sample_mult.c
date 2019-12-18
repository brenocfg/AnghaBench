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
typedef  int /*<<< orphan*/  u32 ;
struct i915_pmu_sample {int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 scalar_t__ mul_u32_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_sample_mult(struct i915_pmu_sample *sample, u32 val, u32 mul)
{
	sample->cur += mul_u32_u32(val, mul);
}