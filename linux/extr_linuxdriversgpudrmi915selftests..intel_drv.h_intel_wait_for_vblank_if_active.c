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
struct intel_crtc {scalar_t__ active; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int) ; 

__attribute__((used)) static inline void
intel_wait_for_vblank_if_active(struct drm_i915_private *dev_priv, int pipe)
{
	const struct intel_crtc *crtc = intel_get_crtc_for_pipe(dev_priv, pipe);

	if (crtc->active)
		intel_wait_for_vblank(dev_priv, pipe);
}