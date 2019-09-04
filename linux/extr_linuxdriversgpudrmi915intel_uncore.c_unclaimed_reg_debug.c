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
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_2__ {int /*<<< orphan*/  mmio_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unclaimed_reg_debug (struct drm_i915_private*,int /*<<< orphan*/  const,int const,int const) ; 
 TYPE_1__ i915_modparams ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline void
unclaimed_reg_debug(struct drm_i915_private *dev_priv,
		    const i915_reg_t reg,
		    const bool read,
		    const bool before)
{
	if (likely(!i915_modparams.mmio_debug))
		return;

	__unclaimed_reg_debug(dev_priv, reg, read, before);
}