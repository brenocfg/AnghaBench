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
typedef  int uint32_t ;
struct intel_crtc_state {int dummy; } ;
struct intel_crtc {int pipe; } ;
struct drm_property_blob {struct drm_color_lut* data; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_color_lut {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ HAS_GMCH_DISPLAY (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DSI ; 
 int /*<<< orphan*/  LGC_PALETTE (int,int) ; 
 int /*<<< orphan*/  PALETTE (int,int) ; 
 int /*<<< orphan*/  assert_dsi_pll_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  assert_pll_enabled (struct drm_i915_private*,int) ; 
 int drm_color_lut_extract (int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void i9xx_load_luts_internal(struct drm_crtc *crtc,
				    struct drm_property_blob *blob,
				    struct intel_crtc_state *crtc_state)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum pipe pipe = intel_crtc->pipe;
	int i;

	if (HAS_GMCH_DISPLAY(dev_priv)) {
		if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI))
			assert_dsi_pll_enabled(dev_priv);
		else
			assert_pll_enabled(dev_priv, pipe);
	}

	if (blob) {
		struct drm_color_lut *lut = blob->data;
		for (i = 0; i < 256; i++) {
			uint32_t word =
				(drm_color_lut_extract(lut[i].red, 8) << 16) |
				(drm_color_lut_extract(lut[i].green, 8) << 8) |
				drm_color_lut_extract(lut[i].blue, 8);

			if (HAS_GMCH_DISPLAY(dev_priv))
				I915_WRITE(PALETTE(pipe, i), word);
			else
				I915_WRITE(LGC_PALETTE(pipe, i), word);
		}
	} else {
		for (i = 0; i < 256; i++) {
			uint32_t word = (i << 16) | (i << 8) | i;

			if (HAS_GMCH_DISPLAY(dev_priv))
				I915_WRITE(PALETTE(pipe, i), word);
			else
				I915_WRITE(LGC_PALETTE(pipe, i), word);
		}
	}
}