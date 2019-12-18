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
struct komeda_wb_connector {int /*<<< orphan*/  base; } ;
struct komeda_events {int* pipes; } ;
struct drm_crtc {TYPE_3__* dev; TYPE_2__* state; } ;
struct komeda_crtc {struct drm_crtc base; int /*<<< orphan*/ * disable_done; struct komeda_wb_connector* wb_conn; TYPE_1__* master; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_5__ {struct drm_pending_vblank_event* event; } ;
struct TYPE_4__ {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_WARN (char*,int /*<<< orphan*/ ) ; 
 int KOMEDA_EVENT_EOW ; 
 int KOMEDA_EVENT_FLIP ; 
 int KOMEDA_EVENT_VSYNC ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  drm_writeback_signal_completion (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void komeda_crtc_handle_event(struct komeda_crtc   *kcrtc,
			      struct komeda_events *evts)
{
	struct drm_crtc *crtc = &kcrtc->base;
	u32 events = evts->pipes[kcrtc->master->id];

	if (events & KOMEDA_EVENT_VSYNC)
		drm_crtc_handle_vblank(crtc);

	if (events & KOMEDA_EVENT_EOW) {
		struct komeda_wb_connector *wb_conn = kcrtc->wb_conn;

		if (wb_conn)
			drm_writeback_signal_completion(&wb_conn->base, 0);
		else
			DRM_WARN("CRTC[%d]: EOW happen but no wb_connector.\n",
				 drm_crtc_index(&kcrtc->base));
	}
	/* will handle it together with the write back support */
	if (events & KOMEDA_EVENT_EOW)
		DRM_DEBUG("EOW.\n");

	if (events & KOMEDA_EVENT_FLIP) {
		unsigned long flags;
		struct drm_pending_vblank_event *event;

		spin_lock_irqsave(&crtc->dev->event_lock, flags);
		if (kcrtc->disable_done) {
			complete_all(kcrtc->disable_done);
			kcrtc->disable_done = NULL;
		} else if (crtc->state->event) {
			event = crtc->state->event;
			/*
			 * Consume event before notifying drm core that flip
			 * happened.
			 */
			crtc->state->event = NULL;
			drm_crtc_send_vblank_event(crtc, event);
		} else {
			DRM_WARN("CRTC[%d]: FLIP happen but no pending commit.\n",
				 drm_crtc_index(&kcrtc->base));
		}
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
	}
}