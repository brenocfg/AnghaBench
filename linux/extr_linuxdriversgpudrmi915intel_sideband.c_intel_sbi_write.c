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
typedef  int u16 ;
struct drm_i915_private {int /*<<< orphan*/  sb_lock; } ;
typedef  enum intel_sbi_destination { ____Placeholder_intel_sbi_destination } intel_sbi_destination ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SBI_ADDR ; 
 int SBI_BUSY ; 
 int SBI_CTL_DEST_ICLK ; 
 int SBI_CTL_DEST_MPHY ; 
 int SBI_CTL_OP_CRWR ; 
 int SBI_CTL_OP_IOWR ; 
 int /*<<< orphan*/  SBI_CTL_STAT ; 
 int /*<<< orphan*/  SBI_DATA ; 
 int SBI_ICLK ; 
 int SBI_RESPONSE_FAIL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

void intel_sbi_write(struct drm_i915_private *dev_priv, u16 reg, u32 value,
		     enum intel_sbi_destination destination)
{
	u32 tmp;

	WARN_ON(!mutex_is_locked(&dev_priv->sb_lock));

	if (intel_wait_for_register(dev_priv,
				    SBI_CTL_STAT, SBI_BUSY, 0,
				    100)) {
		DRM_ERROR("timeout waiting for SBI to become ready\n");
		return;
	}

	I915_WRITE(SBI_ADDR, (reg << 16));
	I915_WRITE(SBI_DATA, value);

	if (destination == SBI_ICLK)
		tmp = SBI_CTL_DEST_ICLK | SBI_CTL_OP_CRWR;
	else
		tmp = SBI_CTL_DEST_MPHY | SBI_CTL_OP_IOWR;
	I915_WRITE(SBI_CTL_STAT, SBI_BUSY | tmp);

	if (intel_wait_for_register(dev_priv,
				    SBI_CTL_STAT,
				    SBI_BUSY,
				    0,
				    100)) {
		DRM_ERROR("timeout waiting for SBI to complete write\n");
		return;
	}

	if (I915_READ(SBI_CTL_STAT) & SBI_RESPONSE_FAIL) {
		DRM_ERROR("error during SBI write of %x to reg %x\n",
			  value, reg);
		return;
	}
}