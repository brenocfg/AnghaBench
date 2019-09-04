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
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct dpu_crtc {int /*<<< orphan*/ * event; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRMID (struct drm_crtc*) ; 
 int /*<<< orphan*/  DRM_DEBUG_VBL (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  trace_dpu_crtc_complete_flip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dpu_crtc_complete_flip(struct drm_crtc *crtc)
{
	struct dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	if (dpu_crtc->event) {
		DRM_DEBUG_VBL("%s: send event: %pK\n", dpu_crtc->name,
			      dpu_crtc->event);
		trace_dpu_crtc_complete_flip(DRMID(crtc));
		drm_crtc_send_vblank_event(crtc, dpu_crtc->event);
		dpu_crtc->event = NULL;
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);
}