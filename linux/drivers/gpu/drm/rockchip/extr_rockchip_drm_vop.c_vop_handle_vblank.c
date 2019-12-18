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
struct drm_crtc {int dummy; } ;
struct vop {int /*<<< orphan*/  fb_unref_work; int /*<<< orphan*/  pending; int /*<<< orphan*/ * event; struct drm_crtc crtc; struct drm_device* drm_dev; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOP_PENDING_FB_UNREF ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_flip_work_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vop_handle_vblank(struct vop *vop)
{
	struct drm_device *drm = vop->drm_dev;
	struct drm_crtc *crtc = &vop->crtc;

	spin_lock(&drm->event_lock);
	if (vop->event) {
		drm_crtc_send_vblank_event(crtc, vop->event);
		drm_crtc_vblank_put(crtc);
		vop->event = NULL;
	}
	spin_unlock(&drm->event_lock);

	if (test_and_clear_bit(VOP_PENDING_FB_UNREF, &vop->pending))
		drm_flip_work_commit(&vop->fb_unref_work, system_unbound_wq);
}