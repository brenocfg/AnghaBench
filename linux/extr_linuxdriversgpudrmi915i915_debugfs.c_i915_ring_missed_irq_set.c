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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  missed_irq_rings; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 int fault_irq_set (struct drm_i915_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_ring_missed_irq_set(void *data, u64 val)
{
	struct drm_i915_private *i915 = data;

	return fault_irq_set(i915, &i915->gpu_error.missed_irq_rings, val);
}