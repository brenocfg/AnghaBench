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
typedef  int /*<<< orphan*/  u32 ;
struct vc4_dev {int dummy; } ;
struct vc4_crtc {int /*<<< orphan*/  channel; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int CRTC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_WRITE (int /*<<< orphan*/ ,int) ; 
 int HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int) ; 
 int PV_VCONTROL_VIDEN ; 
 int /*<<< orphan*/  PV_V_CONTROL ; 
 int /*<<< orphan*/  SCALER_DISPCTRLX (int /*<<< orphan*/ ) ; 
 int SCALER_DISPCTRLX_ENABLE ; 
 int SCALER_DISPCTRLX_RESET ; 
 int /*<<< orphan*/  SCALER_DISPSTATX (int /*<<< orphan*/ ) ; 
 int SCALER_DISPSTATX_EMPTY ; 
 int SCALER_DISPSTATX_FULL ; 
 int /*<<< orphan*/  SCALER_DISPSTATX_MODE ; 
 scalar_t__ SCALER_DISPSTATX_MODE_DISABLED ; 
 scalar_t__ VC4_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  require_hvs_enabled (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static void vc4_crtc_atomic_disable(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct drm_device *dev = crtc->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	u32 chan = vc4_crtc->channel;
	int ret;
	require_hvs_enabled(dev);

	/* Disable vblank irq handling before crtc is disabled. */
	drm_crtc_vblank_off(crtc);

	CRTC_WRITE(PV_V_CONTROL,
		   CRTC_READ(PV_V_CONTROL) & ~PV_VCONTROL_VIDEN);
	ret = wait_for(!(CRTC_READ(PV_V_CONTROL) & PV_VCONTROL_VIDEN), 1);
	WARN_ONCE(ret, "Timeout waiting for !PV_VCONTROL_VIDEN\n");

	if (HVS_READ(SCALER_DISPCTRLX(chan)) &
	    SCALER_DISPCTRLX_ENABLE) {
		HVS_WRITE(SCALER_DISPCTRLX(chan),
			  SCALER_DISPCTRLX_RESET);

		/* While the docs say that reset is self-clearing, it
		 * seems it doesn't actually.
		 */
		HVS_WRITE(SCALER_DISPCTRLX(chan), 0);
	}

	/* Once we leave, the scaler should be disabled and its fifo empty. */

	WARN_ON_ONCE(HVS_READ(SCALER_DISPCTRLX(chan)) & SCALER_DISPCTRLX_RESET);

	WARN_ON_ONCE(VC4_GET_FIELD(HVS_READ(SCALER_DISPSTATX(chan)),
				   SCALER_DISPSTATX_MODE) !=
		     SCALER_DISPSTATX_MODE_DISABLED);

	WARN_ON_ONCE((HVS_READ(SCALER_DISPSTATX(chan)) &
		      (SCALER_DISPSTATX_FULL | SCALER_DISPSTATX_EMPTY)) !=
		     SCALER_DISPSTATX_EMPTY);

	/*
	 * Make sure we issue a vblank event after disabling the CRTC if
	 * someone was waiting it.
	 */
	if (crtc->state->event) {
		unsigned long flags;

		spin_lock_irqsave(&dev->event_lock, flags);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = NULL;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	}
}