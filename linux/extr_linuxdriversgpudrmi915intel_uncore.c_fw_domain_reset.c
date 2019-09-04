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
struct intel_uncore_forcewake_domain {int /*<<< orphan*/  reg_set; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_reset; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_i915_write32 (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fw_domain_reset(struct drm_i915_private *i915,
		const struct intel_uncore_forcewake_domain *d)
{
	/*
	 * We don't really know if the powerwell for the forcewake domain we are
	 * trying to reset here does exist at this point (engines could be fused
	 * off in ICL+), so no waiting for acks
	 */
	__raw_i915_write32(i915, d->reg_set, i915->uncore.fw_reset);
}