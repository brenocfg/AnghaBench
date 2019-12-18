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
struct intel_engine_cs {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTHD ; 
 int /*<<< orphan*/  ENGINE_READ (struct intel_engine_cs const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_READ64 (struct intel_engine_cs const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  RING_ACTHD ; 
 int /*<<< orphan*/  RING_ACTHD_UDW ; 

u64 intel_engine_get_active_head(const struct intel_engine_cs *engine)
{
	struct drm_i915_private *i915 = engine->i915;

	u64 acthd;

	if (INTEL_GEN(i915) >= 8)
		acthd = ENGINE_READ64(engine, RING_ACTHD, RING_ACTHD_UDW);
	else if (INTEL_GEN(i915) >= 4)
		acthd = ENGINE_READ(engine, RING_ACTHD);
	else
		acthd = ENGINE_READ(engine, ACTHD);

	return acthd;
}