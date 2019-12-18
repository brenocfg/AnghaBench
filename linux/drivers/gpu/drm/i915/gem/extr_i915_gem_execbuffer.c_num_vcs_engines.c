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
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int engine_mask; } ;

/* Variables and functions */
 int GENMASK_ULL (scalar_t__,scalar_t__) ; 
 scalar_t__ I915_MAX_VCS ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private const*) ; 
 scalar_t__ VCS0 ; 
 int hweight64 (int) ; 

__attribute__((used)) static int num_vcs_engines(const struct drm_i915_private *i915)
{
	return hweight64(INTEL_INFO(i915)->engine_mask &
			 GENMASK_ULL(VCS0 + I915_MAX_VCS - 1, VCS0));
}