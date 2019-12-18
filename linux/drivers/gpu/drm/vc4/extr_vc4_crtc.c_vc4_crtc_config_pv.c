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
struct vc4_encoder {scalar_t__ type; int clock_select; } ;
struct vc4_crtc {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int flags; int htotal; int hsync_end; int hsync_start; int hdisplay; int crtc_vtotal; int crtc_vsync_end; int crtc_vsync_start; int crtc_vdisplay; } ;
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct drm_crtc {struct drm_crtc_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_WRITE (int /*<<< orphan*/ ,int) ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  PV_CONTROL ; 
 int /*<<< orphan*/  PV_CONTROL_CLK_SELECT ; 
 int PV_CONTROL_CLR_AT_START ; 
 int PV_CONTROL_EN ; 
 int PV_CONTROL_FIFO_CLR ; 
 int /*<<< orphan*/  PV_CONTROL_FIFO_LEVEL ; 
 int /*<<< orphan*/  PV_CONTROL_FORMAT ; 
 int PV_CONTROL_FORMAT_24 ; 
 int PV_CONTROL_FORMAT_DSIV_24 ; 
 int /*<<< orphan*/  PV_CONTROL_PIXEL_REP ; 
 int PV_CONTROL_TRIGGER_UNDERFLOW ; 
 int PV_CONTROL_WAIT_HSTART ; 
 int /*<<< orphan*/  PV_HACT_ACT ; 
 int /*<<< orphan*/  PV_HORZA ; 
 int /*<<< orphan*/  PV_HORZA_HBP ; 
 int /*<<< orphan*/  PV_HORZA_HSYNC ; 
 int /*<<< orphan*/  PV_HORZB ; 
 int /*<<< orphan*/  PV_HORZB_HACTIVE ; 
 int /*<<< orphan*/  PV_HORZB_HFP ; 
 int PV_VCONTROL_CONTINUOUS ; 
 int PV_VCONTROL_DSI ; 
 int PV_VCONTROL_INTERLACE ; 
 int /*<<< orphan*/  PV_VCONTROL_ODD_DELAY ; 
 int /*<<< orphan*/  PV_VERTA ; 
 int /*<<< orphan*/  PV_VERTA_EVEN ; 
 int /*<<< orphan*/  PV_VERTA_VBP ; 
 int /*<<< orphan*/  PV_VERTA_VSYNC ; 
 int /*<<< orphan*/  PV_VERTB ; 
 int /*<<< orphan*/  PV_VERTB_EVEN ; 
 int /*<<< orphan*/  PV_VERTB_VACTIVE ; 
 int /*<<< orphan*/  PV_VERTB_VFP ; 
 int /*<<< orphan*/  PV_VSYNCD_EVEN ; 
 int /*<<< orphan*/  PV_V_CONTROL ; 
 scalar_t__ VC4_ENCODER_TYPE_DSI0 ; 
 scalar_t__ VC4_ENCODER_TYPE_DSI1 ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 
 struct vc4_encoder* to_vc4_encoder (struct drm_encoder*) ; 
 struct drm_encoder* vc4_get_crtc_encoder (struct drm_crtc*) ; 
 int vc4_get_fifo_full_level (int) ; 

__attribute__((used)) static void vc4_crtc_config_pv(struct drm_crtc *crtc)
{
	struct drm_encoder *encoder = vc4_get_crtc_encoder(crtc);
	struct vc4_encoder *vc4_encoder = to_vc4_encoder(encoder);
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	struct drm_crtc_state *state = crtc->state;
	struct drm_display_mode *mode = &state->adjusted_mode;
	bool interlace = mode->flags & DRM_MODE_FLAG_INTERLACE;
	u32 pixel_rep = (mode->flags & DRM_MODE_FLAG_DBLCLK) ? 2 : 1;
	bool is_dsi = (vc4_encoder->type == VC4_ENCODER_TYPE_DSI0 ||
		       vc4_encoder->type == VC4_ENCODER_TYPE_DSI1);
	u32 format = is_dsi ? PV_CONTROL_FORMAT_DSIV_24 : PV_CONTROL_FORMAT_24;

	/* Reset the PV fifo. */
	CRTC_WRITE(PV_CONTROL, 0);
	CRTC_WRITE(PV_CONTROL, PV_CONTROL_FIFO_CLR | PV_CONTROL_EN);
	CRTC_WRITE(PV_CONTROL, 0);

	CRTC_WRITE(PV_HORZA,
		   VC4_SET_FIELD((mode->htotal -
				  mode->hsync_end) * pixel_rep,
				 PV_HORZA_HBP) |
		   VC4_SET_FIELD((mode->hsync_end -
				  mode->hsync_start) * pixel_rep,
				 PV_HORZA_HSYNC));
	CRTC_WRITE(PV_HORZB,
		   VC4_SET_FIELD((mode->hsync_start -
				  mode->hdisplay) * pixel_rep,
				 PV_HORZB_HFP) |
		   VC4_SET_FIELD(mode->hdisplay * pixel_rep, PV_HORZB_HACTIVE));

	CRTC_WRITE(PV_VERTA,
		   VC4_SET_FIELD(mode->crtc_vtotal - mode->crtc_vsync_end,
				 PV_VERTA_VBP) |
		   VC4_SET_FIELD(mode->crtc_vsync_end - mode->crtc_vsync_start,
				 PV_VERTA_VSYNC));
	CRTC_WRITE(PV_VERTB,
		   VC4_SET_FIELD(mode->crtc_vsync_start - mode->crtc_vdisplay,
				 PV_VERTB_VFP) |
		   VC4_SET_FIELD(mode->crtc_vdisplay, PV_VERTB_VACTIVE));

	if (interlace) {
		CRTC_WRITE(PV_VERTA_EVEN,
			   VC4_SET_FIELD(mode->crtc_vtotal -
					 mode->crtc_vsync_end - 1,
					 PV_VERTA_VBP) |
			   VC4_SET_FIELD(mode->crtc_vsync_end -
					 mode->crtc_vsync_start,
					 PV_VERTA_VSYNC));
		CRTC_WRITE(PV_VERTB_EVEN,
			   VC4_SET_FIELD(mode->crtc_vsync_start -
					 mode->crtc_vdisplay,
					 PV_VERTB_VFP) |
			   VC4_SET_FIELD(mode->crtc_vdisplay, PV_VERTB_VACTIVE));

		/* We set up first field even mode for HDMI.  VEC's
		 * NTSC mode would want first field odd instead, once
		 * we support it (to do so, set ODD_FIRST and put the
		 * delay in VSYNCD_EVEN instead).
		 */
		CRTC_WRITE(PV_V_CONTROL,
			   PV_VCONTROL_CONTINUOUS |
			   (is_dsi ? PV_VCONTROL_DSI : 0) |
			   PV_VCONTROL_INTERLACE |
			   VC4_SET_FIELD(mode->htotal * pixel_rep / 2,
					 PV_VCONTROL_ODD_DELAY));
		CRTC_WRITE(PV_VSYNCD_EVEN, 0);
	} else {
		CRTC_WRITE(PV_V_CONTROL,
			   PV_VCONTROL_CONTINUOUS |
			   (is_dsi ? PV_VCONTROL_DSI : 0));
	}

	CRTC_WRITE(PV_HACT_ACT, mode->hdisplay * pixel_rep);

	CRTC_WRITE(PV_CONTROL,
		   VC4_SET_FIELD(format, PV_CONTROL_FORMAT) |
		   VC4_SET_FIELD(vc4_get_fifo_full_level(format),
				 PV_CONTROL_FIFO_LEVEL) |
		   VC4_SET_FIELD(pixel_rep - 1, PV_CONTROL_PIXEL_REP) |
		   PV_CONTROL_CLR_AT_START |
		   PV_CONTROL_TRIGGER_UNDERFLOW |
		   PV_CONTROL_WAIT_HSTART |
		   VC4_SET_FIELD(vc4_encoder->clock_select,
				 PV_CONTROL_CLK_SELECT) |
		   PV_CONTROL_FIFO_CLR |
		   PV_CONTROL_EN);
}