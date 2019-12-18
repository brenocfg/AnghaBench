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
struct i915_ggtt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_gtt_chipset_flush () ; 

__attribute__((used)) static void gmch_ggtt_invalidate(struct i915_ggtt *ggtt)
{
	intel_gtt_chipset_flush();
}