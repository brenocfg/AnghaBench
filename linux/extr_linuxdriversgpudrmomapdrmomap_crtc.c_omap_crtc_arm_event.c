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
struct omap_crtc {int pending; int /*<<< orphan*/ * event; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void omap_crtc_arm_event(struct drm_crtc *crtc)
{
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);

	WARN_ON(omap_crtc->pending);
	omap_crtc->pending = true;

	if (crtc->state->event) {
		omap_crtc->event = crtc->state->event;
		crtc->state->event = NULL;
	}
}