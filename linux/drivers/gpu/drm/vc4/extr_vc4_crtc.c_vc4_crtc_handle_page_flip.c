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
struct TYPE_2__ {scalar_t__ start; } ;
struct vc4_crtc_state {scalar_t__ feed_txp; TYPE_1__ mm; } ;
struct drm_crtc {int /*<<< orphan*/  state; struct drm_device* dev; } ;
struct vc4_crtc {int /*<<< orphan*/  channel; int /*<<< orphan*/ * event; struct drm_crtc base; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 scalar_t__ HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_DISPLACTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_crtc_state* to_vc4_crtc_state (int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_hvs_unmask_underrun (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_crtc_handle_page_flip(struct vc4_crtc *vc4_crtc)
{
	struct drm_crtc *crtc = &vc4_crtc->base;
	struct drm_device *dev = crtc->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc->state);
	u32 chan = vc4_crtc->channel;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	if (vc4_crtc->event &&
	    (vc4_state->mm.start == HVS_READ(SCALER_DISPLACTX(chan)) ||
	     vc4_state->feed_txp)) {
		drm_crtc_send_vblank_event(crtc, vc4_crtc->event);
		vc4_crtc->event = NULL;
		drm_crtc_vblank_put(crtc);

		/* Wait for the page flip to unmask the underrun to ensure that
		 * the display list was updated by the hardware. Before that
		 * happens, the HVS will be using the previous display list with
		 * the CRTC and encoder already reconfigured, leading to
		 * underruns. This can be seen when reconfiguring the CRTC.
		 */
		vc4_hvs_unmask_underrun(dev, vc4_crtc->channel);
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);
}