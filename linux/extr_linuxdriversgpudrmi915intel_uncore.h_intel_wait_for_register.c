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
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int __intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
int intel_wait_for_register(struct drm_i915_private *dev_priv,
			    i915_reg_t reg,
			    u32 mask,
			    u32 value,
			    unsigned int timeout_ms)
{
	return __intel_wait_for_register(dev_priv, reg, mask, value, 2,
					 timeout_ms, NULL);
}