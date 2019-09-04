#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  test_irq_rings; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 int fault_irq_set (struct drm_i915_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_ring_test_irq_set(void *data, u64 val)
{
	struct drm_i915_private *i915 = data;

	val &= INTEL_INFO(i915)->ring_mask;
	DRM_DEBUG_DRIVER("Masking interrupts on rings 0x%08llx\n", val);

	return fault_irq_set(i915, &i915->gpu_error.test_irq_rings, val);
}