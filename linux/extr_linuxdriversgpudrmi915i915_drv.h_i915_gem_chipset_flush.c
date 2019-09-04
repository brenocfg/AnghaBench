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
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gtt_chipset_flush () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void i915_gem_chipset_flush(struct drm_i915_private *dev_priv)
{
	wmb();
	if (INTEL_GEN(dev_priv) < 6)
		intel_gtt_chipset_flush();
}