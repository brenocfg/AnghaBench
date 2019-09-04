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
struct intel_guc {scalar_t__ ggtt_pin_bias; } ;
struct TYPE_4__ {scalar_t__ base; } ;
struct TYPE_3__ {scalar_t__ size; TYPE_2__ guc; } ;
struct drm_i915_private {TYPE_1__ wopcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 

__attribute__((used)) static void guc_init_ggtt_pin_bias(struct intel_guc *guc)
{
	struct drm_i915_private *i915 = guc_to_i915(guc);

	GEM_BUG_ON(!i915->wopcm.size);
	GEM_BUG_ON(i915->wopcm.size < i915->wopcm.guc.base);

	guc->ggtt_pin_bias = i915->wopcm.size - i915->wopcm.guc.base;
}