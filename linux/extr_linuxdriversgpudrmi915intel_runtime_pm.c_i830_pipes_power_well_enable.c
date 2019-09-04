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
struct i915_power_well {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPECONF (int /*<<< orphan*/ ) ; 
 int PIPECONF_ENABLE ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  PIPE_B ; 
 int /*<<< orphan*/  i830_enable_pipe (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i830_pipes_power_well_enable(struct drm_i915_private *dev_priv,
					 struct i915_power_well *power_well)
{
	if ((I915_READ(PIPECONF(PIPE_A)) & PIPECONF_ENABLE) == 0)
		i830_enable_pipe(dev_priv, PIPE_A);
	if ((I915_READ(PIPECONF(PIPE_B)) & PIPECONF_ENABLE) == 0)
		i830_enable_pipe(dev_priv, PIPE_B);
}