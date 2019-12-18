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
struct drm_property_blob {struct drm_color_lut* data; } ;
struct drm_i915_private {int dummy; } ;
struct drm_color_lut {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CGM_PIPE_DEGAMMA (int,int,int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chv_cgm_degamma_ldw (struct drm_color_lut const*) ; 
 int /*<<< orphan*/  chv_cgm_degamma_udw (struct drm_color_lut const*) ; 
 int drm_color_lut_size (struct drm_property_blob const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chv_load_cgm_degamma(struct intel_crtc *crtc,
				 const struct drm_property_blob *blob)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const struct drm_color_lut *lut = blob->data;
	int i, lut_size = drm_color_lut_size(blob);
	enum pipe pipe = crtc->pipe;

	for (i = 0; i < lut_size; i++) {
		I915_WRITE(CGM_PIPE_DEGAMMA(pipe, i, 0),
			   chv_cgm_degamma_ldw(&lut[i]));
		I915_WRITE(CGM_PIPE_DEGAMMA(pipe, i, 1),
			   chv_cgm_degamma_udw(&lut[i]));
	}
}