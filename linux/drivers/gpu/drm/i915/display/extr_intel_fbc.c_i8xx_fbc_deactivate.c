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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  FBC_CONTROL ; 
 int FBC_CTL_EN ; 
 int /*<<< orphan*/  FBC_STATUS ; 
 int /*<<< orphan*/  FBC_STAT_COMPRESSING ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i8xx_fbc_deactivate(struct drm_i915_private *dev_priv)
{
	u32 fbc_ctl;

	/* Disable compression */
	fbc_ctl = I915_READ(FBC_CONTROL);
	if ((fbc_ctl & FBC_CTL_EN) == 0)
		return;

	fbc_ctl &= ~FBC_CTL_EN;
	I915_WRITE(FBC_CONTROL, fbc_ctl);

	/* Wait for compressing bit to clear */
	if (intel_de_wait_for_clear(dev_priv, FBC_STATUS,
				    FBC_STAT_COMPRESSING, 10)) {
		DRM_DEBUG_KMS("FBC idle timed out\n");
		return;
	}
}