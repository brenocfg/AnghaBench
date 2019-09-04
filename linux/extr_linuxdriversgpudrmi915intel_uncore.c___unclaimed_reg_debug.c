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
 scalar_t__ WARN (int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_for_unclaimed_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/  const) ; 
 TYPE_1__ i915_modparams ; 

__attribute__((used)) static void
__unclaimed_reg_debug(struct drm_i915_private *dev_priv,
		      const i915_reg_t reg,
		      const bool read,
		      const bool before)
{
	if (WARN(check_for_unclaimed_mmio(dev_priv) && !before,
		 "Unclaimed %s register 0x%x\n",
		 read ? "read from" : "write to",
		 i915_mmio_reg_offset(reg)))
		/* Only report the first N failures */
		i915_modparams.mmio_debug--;
}