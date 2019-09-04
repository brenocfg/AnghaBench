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
struct omap_crtc {int /*<<< orphan*/  pending_wait; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  omap_crtc_is_pending (struct drm_crtc*) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int omap_crtc_wait_pending(struct drm_crtc *crtc)
{
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);

	/*
	 * Timeout is set to a "sufficiently" high value, which should cover
	 * a single frame refresh even on slower displays.
	 */
	return wait_event_timeout(omap_crtc->pending_wait,
				  !omap_crtc_is_pending(crtc),
				  msecs_to_jiffies(250));
}