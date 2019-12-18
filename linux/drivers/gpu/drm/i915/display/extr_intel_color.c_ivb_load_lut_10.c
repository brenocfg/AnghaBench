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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_property_blob {struct drm_color_lut* data; } ;
struct drm_i915_private {int dummy; } ;
struct drm_color_lut {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREC_PAL_DATA (int) ; 
 int /*<<< orphan*/  PREC_PAL_INDEX (int) ; 
 int drm_color_lut_size (struct drm_property_blob const*) ; 
 int /*<<< orphan*/  ilk_lut_10 (struct drm_color_lut const*) ; 
 int ivb_lut_10_size (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivb_load_lut_10(struct intel_crtc *crtc,
			    const struct drm_property_blob *blob,
			    u32 prec_index)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	int hw_lut_size = ivb_lut_10_size(prec_index);
	const struct drm_color_lut *lut = blob->data;
	int i, lut_size = drm_color_lut_size(blob);
	enum pipe pipe = crtc->pipe;

	for (i = 0; i < hw_lut_size; i++) {
		/* We discard half the user entries in split gamma mode */
		const struct drm_color_lut *entry =
			&lut[i * (lut_size - 1) / (hw_lut_size - 1)];

		I915_WRITE(PREC_PAL_INDEX(pipe), prec_index++);
		I915_WRITE(PREC_PAL_DATA(pipe), ilk_lut_10(entry));
	}

	/*
	 * Reset the index, otherwise it prevents the legacy palette to be
	 * written properly.
	 */
	I915_WRITE(PREC_PAL_INDEX(pipe), 0);
}