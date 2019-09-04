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
 int SBI_CTL_OP_CRRD ; 
 int SBI_CTL_OP_IORD ; 
 int /*<<< orphan*/  SBI_CTL_STAT ; 
 int /*<<< orphan*/  SBI_DATA ; 
 int SBI_ICLK ; 
 int SBI_RESPONSE_FAIL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

u32 intel_sbi_read(struct drm_i915_private *dev_priv, u16 reg,
		   enum intel_sbi_destination destination)
{
	u32 value = 0;
	WARN_ON(!mutex_is_locked(&dev_priv->sb_lock));

	if (intel_wait_for_register(dev_priv,
				    SBI_CTL_STAT, SBI_BUSY, 0,
				    100)) {
		DRM_ERROR("timeout waiting for SBI to become ready\n");
		return 0;
	}

	I915_WRITE(SBI_ADDR, (reg << 16));
	I915_WRITE(SBI_DATA, 0);

	if (destination == SBI_ICLK)
		value = SBI_CTL_DEST_ICLK | SBI_CTL_OP_CRRD;
	else
		value = SBI_CTL_DEST_MPHY | SBI_CTL_OP_IORD;
	I915_WRITE(SBI_CTL_STAT, value | SBI_BUSY);

	if (intel_wait_for_register(dev_priv,
				    SBI_CTL_STAT,
				    SBI_BUSY,
				    0,
				    100)) {
		DRM_ERROR("timeout waiting for SBI to complete read\n");
		return 0;
	}

	if (I915_READ(SBI_CTL_STAT) & SBI_RESPONSE_FAIL) {
		DRM_ERROR("error during SBI read of reg %x\n", reg);
		return 0;
	}

	return I915_READ(SBI_DATA);
}