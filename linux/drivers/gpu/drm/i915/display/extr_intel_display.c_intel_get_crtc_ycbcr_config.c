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
typedef  int u32 ;
struct intel_crtc_state {int lspcon_downsampling; int output_format; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_output_format { ____Placeholder_intel_output_format } intel_output_format ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int INTEL_OUTPUT_FORMAT_INVALID ; 
 int INTEL_OUTPUT_FORMAT_RGB ; 
 int INTEL_OUTPUT_FORMAT_YCBCR420 ; 
 int INTEL_OUTPUT_FORMAT_YCBCR444 ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPEMISC (int /*<<< orphan*/ ) ; 
 int PIPEMISC_OUTPUT_COLORSPACE_YUV ; 
 int PIPEMISC_YUV420_ENABLE ; 
 int PIPEMISC_YUV420_MODE_FULL_BLEND ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_get_crtc_ycbcr_config(struct intel_crtc *crtc,
					struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum intel_output_format output = INTEL_OUTPUT_FORMAT_RGB;

	pipe_config->lspcon_downsampling = false;

	if (IS_BROADWELL(dev_priv) || INTEL_GEN(dev_priv) >= 9) {
		u32 tmp = I915_READ(PIPEMISC(crtc->pipe));

		if (tmp & PIPEMISC_OUTPUT_COLORSPACE_YUV) {
			bool ycbcr420_enabled = tmp & PIPEMISC_YUV420_ENABLE;
			bool blend = tmp & PIPEMISC_YUV420_MODE_FULL_BLEND;

			if (ycbcr420_enabled) {
				/* We support 4:2:0 in full blend mode only */
				if (!blend)
					output = INTEL_OUTPUT_FORMAT_INVALID;
				else if (!(IS_GEMINILAKE(dev_priv) ||
					   INTEL_GEN(dev_priv) >= 10))
					output = INTEL_OUTPUT_FORMAT_INVALID;
				else
					output = INTEL_OUTPUT_FORMAT_YCBCR420;
			} else {
				/*
				 * Currently there is no interface defined to
				 * check user preference between RGB/YCBCR444
				 * or YCBCR420. So the only possible case for
				 * YCBCR444 usage is driving YCBCR420 output
				 * with LSPCON, when pipe is configured for
				 * YCBCR444 output and LSPCON takes care of
				 * downsampling it.
				 */
				pipe_config->lspcon_downsampling = true;
				output = INTEL_OUTPUT_FORMAT_YCBCR444;
			}
		}
	}

	pipe_config->output_format = output;
}