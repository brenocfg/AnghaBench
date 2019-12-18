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
typedef  int /*<<< orphan*/  u64 ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_rc6_residency_ns (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

u64 intel_rc6_residency_us(struct drm_i915_private *dev_priv,
			   i915_reg_t reg)
{
	return DIV_ROUND_UP_ULL(intel_rc6_residency_ns(dev_priv, reg), 1000);
}