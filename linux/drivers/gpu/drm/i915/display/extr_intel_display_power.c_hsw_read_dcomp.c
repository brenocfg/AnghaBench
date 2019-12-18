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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_COMP_BDW ; 
 int /*<<< orphan*/  D_COMP_HSW ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 

__attribute__((used)) static u32 hsw_read_dcomp(struct drm_i915_private *dev_priv)
{
	if (IS_HASWELL(dev_priv))
		return I915_READ(D_COMP_HSW);
	else
		return I915_READ(D_COMP_BDW);
}