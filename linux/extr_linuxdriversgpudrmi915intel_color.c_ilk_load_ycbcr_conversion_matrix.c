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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSC_RGB_TO_YUV_BU ; 
 int /*<<< orphan*/  CSC_RGB_TO_YUV_BV ; 
 int /*<<< orphan*/  CSC_RGB_TO_YUV_BY ; 
 int /*<<< orphan*/  CSC_RGB_TO_YUV_RU_GU ; 
 int /*<<< orphan*/  CSC_RGB_TO_YUV_RV_GV ; 
 int /*<<< orphan*/  CSC_RGB_TO_YUV_RY_GY ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RU_GU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RV_GV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RY_GY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_MODE (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_ME (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_ME (int) ; 
 int /*<<< orphan*/  POSTOFF_RGB_TO_YUV_HI ; 
 int /*<<< orphan*/  POSTOFF_RGB_TO_YUV_LO ; 
 int /*<<< orphan*/  POSTOFF_RGB_TO_YUV_ME ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilk_load_ycbcr_conversion_matrix(struct intel_crtc *intel_crtc)
{
	int pipe = intel_crtc->pipe;
	struct drm_i915_private *dev_priv = to_i915(intel_crtc->base.dev);

	I915_WRITE(PIPE_CSC_PREOFF_HI(pipe), 0);
	I915_WRITE(PIPE_CSC_PREOFF_ME(pipe), 0);
	I915_WRITE(PIPE_CSC_PREOFF_LO(pipe), 0);

	I915_WRITE(PIPE_CSC_COEFF_RU_GU(pipe), CSC_RGB_TO_YUV_RU_GU);
	I915_WRITE(PIPE_CSC_COEFF_BU(pipe), CSC_RGB_TO_YUV_BU);

	I915_WRITE(PIPE_CSC_COEFF_RY_GY(pipe), CSC_RGB_TO_YUV_RY_GY);
	I915_WRITE(PIPE_CSC_COEFF_BY(pipe), CSC_RGB_TO_YUV_BY);

	I915_WRITE(PIPE_CSC_COEFF_RV_GV(pipe), CSC_RGB_TO_YUV_RV_GV);
	I915_WRITE(PIPE_CSC_COEFF_BV(pipe), CSC_RGB_TO_YUV_BV);

	I915_WRITE(PIPE_CSC_POSTOFF_HI(pipe), POSTOFF_RGB_TO_YUV_HI);
	I915_WRITE(PIPE_CSC_POSTOFF_ME(pipe), POSTOFF_RGB_TO_YUV_ME);
	I915_WRITE(PIPE_CSC_POSTOFF_LO(pipe), POSTOFF_RGB_TO_YUV_LO);
	I915_WRITE(PIPE_CSC_MODE(pipe), 0);
}