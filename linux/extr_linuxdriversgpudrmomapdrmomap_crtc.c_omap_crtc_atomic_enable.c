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
struct omap_crtc {int /*<<< orphan*/  name; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  omap_crtc_arm_event (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void omap_crtc_atomic_enable(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);
	int ret;

	DBG("%s", omap_crtc->name);

	spin_lock_irq(&crtc->dev->event_lock);
	drm_crtc_vblank_on(crtc);
	ret = drm_crtc_vblank_get(crtc);
	WARN_ON(ret != 0);

	omap_crtc_arm_event(crtc);
	spin_unlock_irq(&crtc->dev->event_lock);
}