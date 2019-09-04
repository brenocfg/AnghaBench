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
struct vc4_dev {int dummy; } ;
struct vc4_crtc_state {scalar_t__ feed_txp; } ;
struct vc4_crtc {int channel; } ;
struct drm_display_mode {int flags; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {TYPE_1__* state; struct drm_device* dev; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCALER_DISPBKGNDX (int) ; 
 int SCALER_DISPBKGND_AUTOHS ; 
 int SCALER_DISPBKGND_GAMMA ; 
 int SCALER_DISPBKGND_INTERLACE ; 
 int /*<<< orphan*/  SCALER_DISPCTRL ; 
 int /*<<< orphan*/  SCALER_DISPCTRL_DSP3_MUX ; 
 int SCALER_DISPCTRL_DSP3_MUX_MASK ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 
 struct vc4_crtc_state* to_vc4_crtc_state (TYPE_1__*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_crtc_config_pv (struct drm_crtc*) ; 
 int /*<<< orphan*/  vc4_crtc_dump_regs (struct vc4_crtc*) ; 
 int /*<<< orphan*/  vc4_crtc_lut_load (struct drm_crtc*) ; 

__attribute__((used)) static void vc4_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	struct vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc->state);
	struct drm_display_mode *mode = &crtc->state->adjusted_mode;
	bool interlace = mode->flags & DRM_MODE_FLAG_INTERLACE;
	bool debug_dump_regs = false;

	if (debug_dump_regs) {
		DRM_INFO("CRTC %d regs before:\n", drm_crtc_index(crtc));
		vc4_crtc_dump_regs(vc4_crtc);
	}

	if (vc4_crtc->channel == 2) {
		u32 dispctrl;
		u32 dsp3_mux;

		/*
		 * SCALER_DISPCTRL_DSP3 = X, where X < 2 means 'connect DSP3 to
		 * FIFO X'.
		 * SCALER_DISPCTRL_DSP3 = 3 means 'disable DSP 3'.
		 *
		 * DSP3 is connected to FIFO2 unless the transposer is
		 * enabled. In this case, FIFO 2 is directly accessed by the
		 * TXP IP, and we need to disable the FIFO2 -> pixelvalve1
		 * route.
		 */
		if (vc4_state->feed_txp)
			dsp3_mux = VC4_SET_FIELD(3, SCALER_DISPCTRL_DSP3_MUX);
		else
			dsp3_mux = VC4_SET_FIELD(2, SCALER_DISPCTRL_DSP3_MUX);

		dispctrl = HVS_READ(SCALER_DISPCTRL) &
			   ~SCALER_DISPCTRL_DSP3_MUX_MASK;
		HVS_WRITE(SCALER_DISPCTRL, dispctrl | dsp3_mux);
	}

	if (!vc4_state->feed_txp)
		vc4_crtc_config_pv(crtc);

	HVS_WRITE(SCALER_DISPBKGNDX(vc4_crtc->channel),
		  SCALER_DISPBKGND_AUTOHS |
		  SCALER_DISPBKGND_GAMMA |
		  (interlace ? SCALER_DISPBKGND_INTERLACE : 0));

	/* Reload the LUT, since the SRAMs would have been disabled if
	 * all CRTCs had SCALER_DISPBKGND_GAMMA unset at once.
	 */
	vc4_crtc_lut_load(crtc);

	if (debug_dump_regs) {
		DRM_INFO("CRTC %d regs after:\n", drm_crtc_index(crtc));
		vc4_crtc_dump_regs(vc4_crtc);
	}
}