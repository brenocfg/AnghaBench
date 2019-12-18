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
struct intel_crtc {scalar_t__ pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private const*) ; 
 scalar_t__ IS_I915G (struct drm_i915_private const*) ; 
 scalar_t__ PIPE_A ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_crtc_supports_double_wide(const struct intel_crtc *crtc)
{
	const struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	/* GDG double wide on either pipe, otherwise pipe A only */
	return INTEL_GEN(dev_priv) < 4 &&
		(crtc->pipe == PIPE_A || IS_I915G(dev_priv));
}