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
struct omap_crtc_state {int /*<<< orphan*/  manually_updated; } ;
struct omap_crtc {int /*<<< orphan*/  update_work; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 
 struct omap_crtc_state* to_omap_crtc_state (int /*<<< orphan*/ ) ; 

void omap_crtc_flush(struct drm_crtc *crtc)
{
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);
	struct omap_crtc_state *omap_state = to_omap_crtc_state(crtc->state);

	if (!omap_state->manually_updated)
		return;

	if (!delayed_work_pending(&omap_crtc->update_work))
		schedule_delayed_work(&omap_crtc->update_work, 0);
}