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
struct i915_power_well {int hw_enabled; TYPE_1__* ops; int /*<<< orphan*/  name; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct drm_i915_private*,struct i915_power_well*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void intel_power_well_enable(struct drm_i915_private *dev_priv,
				    struct i915_power_well *power_well)
{
	DRM_DEBUG_KMS("enabling %s\n", power_well->name);
	power_well->ops->enable(dev_priv, power_well);
	power_well->hw_enabled = true;
}