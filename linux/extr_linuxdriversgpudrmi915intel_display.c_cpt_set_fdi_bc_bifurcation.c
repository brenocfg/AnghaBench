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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 int FDI_BC_BIFURCATION_SELECT ; 
 int /*<<< orphan*/  FDI_RX_CTL (int /*<<< orphan*/ ) ; 
 int FDI_RX_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPE_B ; 
 int /*<<< orphan*/  PIPE_C ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOUTH_CHICKEN1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void cpt_set_fdi_bc_bifurcation(struct drm_device *dev, bool enable)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	uint32_t temp;

	temp = I915_READ(SOUTH_CHICKEN1);
	if (!!(temp & FDI_BC_BIFURCATION_SELECT) == enable)
		return;

	WARN_ON(I915_READ(FDI_RX_CTL(PIPE_B)) & FDI_RX_ENABLE);
	WARN_ON(I915_READ(FDI_RX_CTL(PIPE_C)) & FDI_RX_ENABLE);

	temp &= ~FDI_BC_BIFURCATION_SELECT;
	if (enable)
		temp |= FDI_BC_BIFURCATION_SELECT;

	DRM_DEBUG_KMS("%sabling fdi C rx\n", enable ? "en" : "dis");
	I915_WRITE(SOUTH_CHICKEN1, temp);
	POSTING_READ(SOUTH_CHICKEN1);
}