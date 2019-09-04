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
struct mdp4_crtc {int /*<<< orphan*/  name; struct drm_pending_vblank_event* event; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void complete_flip(struct drm_crtc *crtc, struct drm_file *file)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct drm_pending_vblank_event *event;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	event = mdp4_crtc->event;
	if (event) {
		mdp4_crtc->event = NULL;
		DBG("%s: send event: %p", mdp4_crtc->name, event);
		drm_crtc_send_vblank_event(crtc, event);
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);
}