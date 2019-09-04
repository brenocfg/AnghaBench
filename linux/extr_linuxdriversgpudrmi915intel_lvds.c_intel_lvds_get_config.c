#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_lvds_encoder {int /*<<< orphan*/  reg; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_4__ base; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_7__ {TYPE_2__ adjusted_mode; } ;
struct TYPE_5__ {int lvds_border_bits; int control; } ;
struct intel_crtc_state {int /*<<< orphan*/  port_clock; TYPE_3__ base; TYPE_1__ gmch_pfit; int /*<<< orphan*/  output_types; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 int LVDS_BORDER_ENABLE ; 
 int LVDS_HSYNC_POLARITY ; 
 int LVDS_VSYNC_POLARITY ; 
 int PANEL_8TO6_DITHER_ENABLE ; 
 int /*<<< orphan*/  PFIT_CONTROL ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_lvds_encoder* to_lvds_encoder (TYPE_4__*) ; 

__attribute__((used)) static void intel_lvds_get_config(struct intel_encoder *encoder,
				  struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	u32 tmp, flags = 0;

	pipe_config->output_types |= BIT(INTEL_OUTPUT_LVDS);

	tmp = I915_READ(lvds_encoder->reg);
	if (tmp & LVDS_HSYNC_POLARITY)
		flags |= DRM_MODE_FLAG_NHSYNC;
	else
		flags |= DRM_MODE_FLAG_PHSYNC;
	if (tmp & LVDS_VSYNC_POLARITY)
		flags |= DRM_MODE_FLAG_NVSYNC;
	else
		flags |= DRM_MODE_FLAG_PVSYNC;

	pipe_config->base.adjusted_mode.flags |= flags;

	if (INTEL_GEN(dev_priv) < 5)
		pipe_config->gmch_pfit.lvds_border_bits =
			tmp & LVDS_BORDER_ENABLE;

	/* gen2/3 store dither state in pfit control, needs to match */
	if (INTEL_GEN(dev_priv) < 4) {
		tmp = I915_READ(PFIT_CONTROL);

		pipe_config->gmch_pfit.control |= tmp & PANEL_8TO6_DITHER_ENABLE;
	}

	pipe_config->base.adjusted_mode.crtc_clock = pipe_config->port_clock;
}