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
struct TYPE_4__ {scalar_t__ visible; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct intel_fbc {int visible_pipes_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  no_fbc_on_multiple_pipes (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool multiple_pipes_ok(struct intel_crtc *crtc,
			      struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_fbc *fbc = &dev_priv->fbc;
	enum pipe pipe = crtc->pipe;

	/* Don't even bother tracking anything we don't need. */
	if (!no_fbc_on_multiple_pipes(dev_priv))
		return true;

	if (plane_state->base.visible)
		fbc->visible_pipes_mask |= (1 << pipe);
	else
		fbc->visible_pipes_mask &= ~(1 << pipe);

	return (fbc->visible_pipes_mask & ~(1 << pipe)) != 0;
}