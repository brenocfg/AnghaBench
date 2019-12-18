#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ csc_enable; scalar_t__ gamma_enable; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MCURSOR_GAMMA_ENABLE ; 
 int /*<<< orphan*/  MCURSOR_PIPE_CSC_ENABLE ; 
 int /*<<< orphan*/  MCURSOR_PIPE_SELECT (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i9xx_cursor_ctl_crtc(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	u32 cntl = 0;

	if (INTEL_GEN(dev_priv) >= 11)
		return cntl;

	if (crtc_state->gamma_enable)
		cntl = MCURSOR_GAMMA_ENABLE;

	if (crtc_state->csc_enable)
		cntl |= MCURSOR_PIPE_CSC_ENABLE;

	if (INTEL_GEN(dev_priv) < 5 && !IS_G4X(dev_priv))
		cntl |= MCURSOR_PIPE_SELECT(crtc->pipe);

	return cntl;
}