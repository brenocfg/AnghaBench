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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_4__ {int pipe; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVIDEO_DIP_CTL (int) ; 
 int VIDEO_DIP_ENABLE ; 
 int VIDEO_DIP_ENABLE_AVI ; 
 int VIDEO_DIP_ENABLE_GAMUT ; 
 int VIDEO_DIP_ENABLE_GCP ; 
 int VIDEO_DIP_ENABLE_SPD ; 
 int VIDEO_DIP_ENABLE_VENDOR ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cpt_infoframe_enabled(struct drm_encoder *encoder,
				  const struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->dev);
	enum pipe pipe = to_intel_crtc(pipe_config->base.crtc)->pipe;
	u32 val = I915_READ(TVIDEO_DIP_CTL(pipe));

	if ((val & VIDEO_DIP_ENABLE) == 0)
		return false;

	return val & (VIDEO_DIP_ENABLE_AVI |
		      VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		      VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
}