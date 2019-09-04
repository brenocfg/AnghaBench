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
struct i915_power_well {scalar_t__ id; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHV_DISP_PW_PIPE_A ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  chv_set_pipe_power_well (struct drm_i915_private*,struct i915_power_well*,int) ; 
 int /*<<< orphan*/  vlv_display_power_well_init (struct drm_i915_private*) ; 

__attribute__((used)) static void chv_pipe_power_well_enable(struct drm_i915_private *dev_priv,
				       struct i915_power_well *power_well)
{
	WARN_ON_ONCE(power_well->id != CHV_DISP_PW_PIPE_A);

	chv_set_pipe_power_well(dev_priv, power_well, true);

	vlv_display_power_well_init(dev_priv);
}