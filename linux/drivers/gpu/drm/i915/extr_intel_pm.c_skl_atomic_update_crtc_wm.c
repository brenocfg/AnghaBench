#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct skl_pipe_wm {int /*<<< orphan*/  linetime; } ;
struct TYPE_9__ {struct skl_pipe_wm optimal; } ;
struct TYPE_10__ {TYPE_4__ skl; } ;
struct TYPE_7__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_5__ wm; TYPE_2__ base; } ;
struct intel_crtc {int pipe; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int dirty_pipes; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct intel_atomic_state {TYPE_1__ wm_results; TYPE_3__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_WM_LINETIME (int) ; 
 int drm_crtc_mask (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_atomic_update_crtc_wm(struct intel_atomic_state *state,
				      struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(state->base.dev);
	struct skl_pipe_wm *pipe_wm = &crtc_state->wm.skl.optimal;
	enum pipe pipe = crtc->pipe;

	if (!(state->wm_results.dirty_pipes & drm_crtc_mask(&crtc->base)))
		return;

	I915_WRITE(PIPE_WM_LINETIME(pipe), pipe_wm->linetime);
}