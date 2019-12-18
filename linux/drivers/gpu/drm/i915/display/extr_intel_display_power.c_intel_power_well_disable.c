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
struct i915_power_well {int hw_enabled; TYPE_2__* desc; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable ) (struct drm_i915_private*,struct i915_power_well*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void intel_power_well_disable(struct drm_i915_private *dev_priv,
				     struct i915_power_well *power_well)
{
	DRM_DEBUG_KMS("disabling %s\n", power_well->desc->name);
	power_well->hw_enabled = false;
	power_well->desc->ops->disable(dev_priv, power_well);
}