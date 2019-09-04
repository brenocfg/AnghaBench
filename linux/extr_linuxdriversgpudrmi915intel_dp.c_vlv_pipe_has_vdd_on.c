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
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int EDP_FORCE_VDD ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP_CONTROL (int) ; 

__attribute__((used)) static bool vlv_pipe_has_vdd_on(struct drm_i915_private *dev_priv,
				enum pipe pipe)
{
	return I915_READ(PP_CONTROL(pipe)) & EDP_FORCE_VDD;
}