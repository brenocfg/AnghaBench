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
struct intel_crtc_state {int /*<<< orphan*/  cpu_transcoder; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSW_TVIDEO_DIP_CTL (int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int VIDEO_DIP_ENABLE_AVI_HSW ; 
 int VIDEO_DIP_ENABLE_GCP_HSW ; 
 int VIDEO_DIP_ENABLE_GMP_HSW ; 
 int VIDEO_DIP_ENABLE_SPD_HSW ; 
 int VIDEO_DIP_ENABLE_VSC_HSW ; 
 int VIDEO_DIP_ENABLE_VS_HSW ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hsw_infoframe_enabled(struct drm_encoder *encoder,
				  const struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->dev);
	u32 val = I915_READ(HSW_TVIDEO_DIP_CTL(pipe_config->cpu_transcoder));

	return val & (VIDEO_DIP_ENABLE_VSC_HSW | VIDEO_DIP_ENABLE_AVI_HSW |
		      VIDEO_DIP_ENABLE_GCP_HSW | VIDEO_DIP_ENABLE_VS_HSW |
		      VIDEO_DIP_ENABLE_GMP_HSW | VIDEO_DIP_ENABLE_SPD_HSW);
}