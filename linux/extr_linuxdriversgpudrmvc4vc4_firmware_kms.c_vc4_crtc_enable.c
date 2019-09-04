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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_3__* cursor; TYPE_2__* primary; } ;
struct TYPE_8__ {scalar_t__ fb; } ;
struct TYPE_7__ {TYPE_4__* state; } ;
struct TYPE_6__ {TYPE_1__* state; } ;
struct TYPE_5__ {scalar_t__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc4_cursor_plane_atomic_update (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  vc4_plane_set_primary_blank (TYPE_2__*,int) ; 

__attribute__((used)) static void vc4_crtc_enable(struct drm_crtc *crtc, struct drm_crtc_state *old_state)
{
	/* Unblank the planes (if they're supposed to be displayed). */
	if (crtc->primary->state->fb)
		vc4_plane_set_primary_blank(crtc->primary, false);
	if (crtc->cursor->state->fb) {
		vc4_cursor_plane_atomic_update(crtc->cursor,
					       crtc->cursor->state);
	}
}