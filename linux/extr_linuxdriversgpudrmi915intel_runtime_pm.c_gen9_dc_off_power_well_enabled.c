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
 int /*<<< orphan*/  DC_STATE_EN ; 
 int DC_STATE_EN_UPTO_DC5_DC6_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gen9_dc_off_power_well_enabled(struct drm_i915_private *dev_priv,
					   struct i915_power_well *power_well)
{
	return (I915_READ(DC_STATE_EN) & DC_STATE_EN_UPTO_DC5_DC6_MASK) == 0;
}