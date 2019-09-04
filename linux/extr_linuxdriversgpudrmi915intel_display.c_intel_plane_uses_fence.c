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
struct TYPE_3__ {int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {scalar_t__ has_fbc; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_plane_uses_fence(const struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);

	return INTEL_GEN(dev_priv) < 4 || plane->has_fbc;
}