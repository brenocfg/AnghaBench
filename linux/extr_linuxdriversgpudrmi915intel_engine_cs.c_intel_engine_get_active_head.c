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
typedef  int /*<<< orphan*/  u64 ;
struct intel_engine_cs {int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTHD ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ64_2x32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  RING_ACTHD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_ACTHD_UDW (int /*<<< orphan*/ ) ; 

u64 intel_engine_get_active_head(const struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	u64 acthd;

	if (INTEL_GEN(dev_priv) >= 8)
		acthd = I915_READ64_2x32(RING_ACTHD(engine->mmio_base),
					 RING_ACTHD_UDW(engine->mmio_base));
	else if (INTEL_GEN(dev_priv) >= 4)
		acthd = I915_READ(RING_ACTHD(engine->mmio_base));
	else
		acthd = I915_READ(ACTHD);

	return acthd;
}