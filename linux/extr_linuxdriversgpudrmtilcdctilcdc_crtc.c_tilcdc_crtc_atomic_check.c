#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_display_mode {int /*<<< orphan*/  name; } ;
struct drm_crtc_state {TYPE_3__* state; int /*<<< orphan*/  active; struct drm_display_mode mode; } ;
struct drm_crtc {scalar_t__ primary; TYPE_4__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_2__* planes; } ;
struct TYPE_6__ {scalar_t__ ptr; TYPE_1__* state; } ;
struct TYPE_5__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int tilcdc_crtc_mode_valid (struct drm_crtc*,struct drm_display_mode*) ; 

__attribute__((used)) static int tilcdc_crtc_atomic_check(struct drm_crtc *crtc,
				    struct drm_crtc_state *state)
{
	struct drm_display_mode *mode = &state->mode;
	int ret;

	/* If we are not active we don't care */
	if (!state->active)
		return 0;

	if (state->state->planes[0].ptr != crtc->primary ||
	    state->state->planes[0].state == NULL ||
	    state->state->planes[0].state->crtc != crtc) {
		dev_dbg(crtc->dev->dev, "CRTC primary plane must be present");
		return -EINVAL;
	}

	ret = tilcdc_crtc_mode_valid(crtc, mode);
	if (ret) {
		dev_dbg(crtc->dev->dev, "Mode \"%s\" not valid", mode->name);
		return -EINVAL;
	}

	return 0;
}