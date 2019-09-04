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
typedef  int u32 ;
struct intel_crtc_state {int pipe_bpp; scalar_t__ ycbcr420; scalar_t__ dither; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; struct intel_crtc_state* config; } ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPEMISC (int /*<<< orphan*/ ) ; 
 int PIPEMISC_DITHER_10_BPC ; 
 int PIPEMISC_DITHER_12_BPC ; 
 int PIPEMISC_DITHER_6_BPC ; 
 int PIPEMISC_DITHER_8_BPC ; 
 int PIPEMISC_DITHER_ENABLE ; 
 int PIPEMISC_DITHER_TYPE_SP ; 
 int PIPEMISC_OUTPUT_COLORSPACE_YUV ; 
 int PIPEMISC_YUV420_ENABLE ; 
 int PIPEMISC_YUV420_MODE_FULL_BLEND ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void haswell_set_pipemisc(struct drm_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_crtc_state *config = intel_crtc->config;

	if (IS_BROADWELL(dev_priv) || INTEL_GEN(dev_priv) >= 9) {
		u32 val = 0;

		switch (intel_crtc->config->pipe_bpp) {
		case 18:
			val |= PIPEMISC_DITHER_6_BPC;
			break;
		case 24:
			val |= PIPEMISC_DITHER_8_BPC;
			break;
		case 30:
			val |= PIPEMISC_DITHER_10_BPC;
			break;
		case 36:
			val |= PIPEMISC_DITHER_12_BPC;
			break;
		default:
			/* Case prevented by pipe_config_set_bpp. */
			BUG();
		}

		if (intel_crtc->config->dither)
			val |= PIPEMISC_DITHER_ENABLE | PIPEMISC_DITHER_TYPE_SP;

		if (config->ycbcr420) {
			val |= PIPEMISC_OUTPUT_COLORSPACE_YUV |
				PIPEMISC_YUV420_ENABLE |
				PIPEMISC_YUV420_MODE_FULL_BLEND;
		}

		I915_WRITE(PIPEMISC(intel_crtc->pipe), val);
	}
}