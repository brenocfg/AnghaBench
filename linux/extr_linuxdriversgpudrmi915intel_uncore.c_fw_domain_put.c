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
struct TYPE_2__ {int /*<<< orphan*/  fw_clear; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_i915_write32 (struct drm_i915_private const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fw_domain_put(const struct drm_i915_private *i915,
	      const struct intel_uncore_forcewake_domain *d)
{
	__raw_i915_write32(i915, d->reg_set, i915->uncore.fw_clear);
}