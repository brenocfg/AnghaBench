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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int const) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RU_GU (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RV_GV (int) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RY_GY (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_ME (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_HI (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_LO (int) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_ME (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilk_update_pipe_csc(struct intel_crtc *crtc,
				const u16 preoff[3],
				const u16 coeff[9],
				const u16 postoff[3])
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;

	I915_WRITE(PIPE_CSC_PREOFF_HI(pipe), preoff[0]);
	I915_WRITE(PIPE_CSC_PREOFF_ME(pipe), preoff[1]);
	I915_WRITE(PIPE_CSC_PREOFF_LO(pipe), preoff[2]);

	I915_WRITE(PIPE_CSC_COEFF_RY_GY(pipe), coeff[0] << 16 | coeff[1]);
	I915_WRITE(PIPE_CSC_COEFF_BY(pipe), coeff[2] << 16);

	I915_WRITE(PIPE_CSC_COEFF_RU_GU(pipe), coeff[3] << 16 | coeff[4]);
	I915_WRITE(PIPE_CSC_COEFF_BU(pipe), coeff[5] << 16);

	I915_WRITE(PIPE_CSC_COEFF_RV_GV(pipe), coeff[6] << 16 | coeff[7]);
	I915_WRITE(PIPE_CSC_COEFF_BV(pipe), coeff[8] << 16);

	if (INTEL_GEN(dev_priv) >= 7) {
		I915_WRITE(PIPE_CSC_POSTOFF_HI(pipe), postoff[0]);
		I915_WRITE(PIPE_CSC_POSTOFF_ME(pipe), postoff[1]);
		I915_WRITE(PIPE_CSC_POSTOFF_LO(pipe), postoff[2]);
	}
}