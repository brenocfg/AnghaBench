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
struct intel_crtc {int dummy; } ;
struct drm_i915_private {struct intel_crtc** pipe_to_crtc_mapping; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */

__attribute__((used)) static inline struct intel_crtc *
intel_get_crtc_for_pipe(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	return dev_priv->pipe_to_crtc_mapping[pipe];
}