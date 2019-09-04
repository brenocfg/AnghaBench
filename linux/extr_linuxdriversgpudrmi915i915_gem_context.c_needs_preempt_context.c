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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int HAS_LOGICAL_RING_PREEMPTION (struct drm_i915_private*) ; 

__attribute__((used)) static bool needs_preempt_context(struct drm_i915_private *i915)
{
	return HAS_LOGICAL_RING_PREEMPTION(i915);
}