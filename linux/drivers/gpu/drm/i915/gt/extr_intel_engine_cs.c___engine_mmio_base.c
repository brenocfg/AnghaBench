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
typedef  int /*<<< orphan*/  u32 ;
struct engine_mmio_base {scalar_t__ gen; int /*<<< orphan*/  base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ INTEL_GEN (struct drm_i915_private*) ; 
 int MAX_MMIO_BASES ; 

__attribute__((used)) static u32 __engine_mmio_base(struct drm_i915_private *i915,
			      const struct engine_mmio_base *bases)
{
	int i;

	for (i = 0; i < MAX_MMIO_BASES; i++)
		if (INTEL_GEN(i915) >= bases[i].gen)
			break;

	GEM_BUG_ON(i == MAX_MMIO_BASES);
	GEM_BUG_ON(!bases[i].base);

	return bases[i].base;
}