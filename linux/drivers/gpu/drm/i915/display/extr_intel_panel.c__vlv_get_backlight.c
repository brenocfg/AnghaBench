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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int BACKLIGHT_DUTY_CYCLE_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PIPE_A ; 
 int PIPE_B ; 
 int /*<<< orphan*/  VLV_BLC_PWM_CTL (int) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static u32 _vlv_get_backlight(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	if (WARN_ON(pipe != PIPE_A && pipe != PIPE_B))
		return 0;

	return I915_READ(VLV_BLC_PWM_CTL(pipe)) & BACKLIGHT_DUTY_CYCLE_MASK;
}