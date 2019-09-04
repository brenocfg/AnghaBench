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
struct vc4_dev {int dummy; } ;
struct vc4_crtc_state {scalar_t__ feed_txp; } ;
struct vc4_crtc {int /*<<< orphan*/  channel; } ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; struct drm_device* dev; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int CRTC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int) ; 
 int PV_VCONTROL_VIDEN ; 
 int /*<<< orphan*/  PV_V_CONTROL ; 
 int /*<<< orphan*/  SCALER_DISPCTRLX (int /*<<< orphan*/ ) ; 
 int SCALER_DISPCTRLX_ENABLE ; 
 int /*<<< orphan*/  SCALER_DISPCTRLX_HEIGHT ; 
 int SCALER_DISPCTRLX_ONESHOT ; 
 int /*<<< orphan*/  SCALER_DISPCTRLX_WIDTH ; 
 int VC4_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  require_hvs_enabled (struct drm_device*) ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 
 struct vc4_crtc_state* to_vc4_crtc_state (TYPE_1__*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_crtc_update_dlist (struct drm_crtc*) ; 

__attribute__((used)) static void vc4_crtc_atomic_enable(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_state)
{
	struct drm_device *dev = crtc->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	struct vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc->state);
	struct drm_display_mode *mode = &crtc->state->adjusted_mode;

	require_hvs_enabled(dev);

	/* Enable vblank irq handling before crtc is started otherwise
	 * drm_crtc_get_vblank() fails in vc4_crtc_update_dlist().
	 */
	drm_crtc_vblank_on(crtc);
	vc4_crtc_update_dlist(crtc);

	/* Turn on the scaler, which will wait for vstart to start
	 * compositing.
	 * When feeding the transposer, we should operate in oneshot
	 * mode.
	 */
	HVS_WRITE(SCALER_DISPCTRLX(vc4_crtc->channel),
		  VC4_SET_FIELD(mode->hdisplay, SCALER_DISPCTRLX_WIDTH) |
		  VC4_SET_FIELD(mode->vdisplay, SCALER_DISPCTRLX_HEIGHT) |
		  SCALER_DISPCTRLX_ENABLE |
		  (vc4_state->feed_txp ? SCALER_DISPCTRLX_ONESHOT : 0));

	/* When feeding the transposer block the pixelvalve is unneeded and
	 * should not be enabled.
	 */
	if (!vc4_state->feed_txp)
		CRTC_WRITE(PV_V_CONTROL,
			   CRTC_READ(PV_V_CONTROL) | PV_VCONTROL_VIDEN);
}