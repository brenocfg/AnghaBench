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
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int FDI_MPHY_IOSFSB_RESET_CTL ; 
 int FDI_MPHY_IOSFSB_RESET_STATUS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOUTH_CHICKEN2 ; 
 scalar_t__ wait_for_us (int,int) ; 

__attribute__((used)) static void lpt_reset_fdi_mphy(struct drm_i915_private *dev_priv)
{
	u32 tmp;

	tmp = I915_READ(SOUTH_CHICKEN2);
	tmp |= FDI_MPHY_IOSFSB_RESET_CTL;
	I915_WRITE(SOUTH_CHICKEN2, tmp);

	if (wait_for_us(I915_READ(SOUTH_CHICKEN2) &
			FDI_MPHY_IOSFSB_RESET_STATUS, 100))
		DRM_ERROR("FDI mPHY reset assert timeout\n");

	tmp = I915_READ(SOUTH_CHICKEN2);
	tmp &= ~FDI_MPHY_IOSFSB_RESET_CTL;
	I915_WRITE(SOUTH_CHICKEN2, tmp);

	if (wait_for_us((I915_READ(SOUTH_CHICKEN2) &
			 FDI_MPHY_IOSFSB_RESET_STATUS) == 0, 100))
		DRM_ERROR("FDI mPHY reset de-assert timeout\n");
}