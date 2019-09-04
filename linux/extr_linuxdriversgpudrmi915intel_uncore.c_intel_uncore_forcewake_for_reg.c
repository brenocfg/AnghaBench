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
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 unsigned int FW_REG_READ ; 
 unsigned int FW_REG_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int intel_uncore_forcewake_for_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_uncore_forcewake_for_write (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 

enum forcewake_domains
intel_uncore_forcewake_for_reg(struct drm_i915_private *dev_priv,
			       i915_reg_t reg, unsigned int op)
{
	enum forcewake_domains fw_domains = 0;

	WARN_ON(!op);

	if (intel_vgpu_active(dev_priv))
		return 0;

	if (op & FW_REG_READ)
		fw_domains = intel_uncore_forcewake_for_read(dev_priv, reg);

	if (op & FW_REG_WRITE)
		fw_domains |= intel_uncore_forcewake_for_write(dev_priv, reg);

	return fw_domains;
}