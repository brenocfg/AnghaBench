#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dvo_srcdim_reg; int /*<<< orphan*/  dvo_reg; } ;
struct intel_dvo {TYPE_3__ dev; } ;
struct drm_display_mode {int flags; int crtc_hdisplay; int crtc_vdisplay; } ;
struct TYPE_5__ {struct drm_display_mode adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int DVO_BLANK_ACTIVE_HIGH ; 
 int DVO_BORDER_ENABLE ; 
 int DVO_DATA_ORDER_FP ; 
 int DVO_DATA_ORDER_GBRG ; 
 int DVO_HSYNC_ACTIVE_HIGH ; 
 int DVO_PIPE_SEL (int) ; 
 int DVO_PIPE_STALL ; 
 int DVO_PRESERVE_MASK ; 
 int DVO_SRCDIM_HORIZONTAL_SHIFT ; 
 int DVO_SRCDIM_VERTICAL_SHIFT ; 
 int DVO_VSYNC_ACTIVE_HIGH ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 struct intel_dvo* enc_to_dvo (struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dvo_pre_enable(struct intel_encoder *encoder,
				 const struct intel_crtc_state *pipe_config,
				 const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crtc *crtc = to_intel_crtc(pipe_config->base.crtc);
	const struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	struct intel_dvo *intel_dvo = enc_to_dvo(encoder);
	int pipe = crtc->pipe;
	u32 dvo_val;
	i915_reg_t dvo_reg = intel_dvo->dev.dvo_reg;
	i915_reg_t dvo_srcdim_reg = intel_dvo->dev.dvo_srcdim_reg;

	/* Save the data order, since I don't know what it should be set to. */
	dvo_val = I915_READ(dvo_reg) &
		  (DVO_PRESERVE_MASK | DVO_DATA_ORDER_GBRG);
	dvo_val |= DVO_DATA_ORDER_FP | DVO_BORDER_ENABLE |
		   DVO_BLANK_ACTIVE_HIGH;

	dvo_val |= DVO_PIPE_SEL(pipe);
	dvo_val |= DVO_PIPE_STALL;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		dvo_val |= DVO_HSYNC_ACTIVE_HIGH;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		dvo_val |= DVO_VSYNC_ACTIVE_HIGH;

	/*I915_WRITE(DVOB_SRCDIM,
	  (adjusted_mode->crtc_hdisplay << DVO_SRCDIM_HORIZONTAL_SHIFT) |
	  (adjusted_mode->crtc_vdisplay << DVO_SRCDIM_VERTICAL_SHIFT));*/
	I915_WRITE(dvo_srcdim_reg,
		   (adjusted_mode->crtc_hdisplay << DVO_SRCDIM_HORIZONTAL_SHIFT) |
		   (adjusted_mode->crtc_vdisplay << DVO_SRCDIM_VERTICAL_SHIFT));
	/*I915_WRITE(DVOB, dvo_val);*/
	I915_WRITE(dvo_reg, dvo_val);
}