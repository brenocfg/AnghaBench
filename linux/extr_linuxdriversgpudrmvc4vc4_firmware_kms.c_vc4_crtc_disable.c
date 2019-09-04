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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  primary; TYPE_1__* cursor; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc4_cursor_plane_atomic_disable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_plane_set_primary_blank (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vc4_crtc_disable(struct drm_crtc *crtc, struct drm_crtc_state *old_state)
{
	/* Always turn the planes off on CRTC disable. In DRM, planes
	 * are enabled/disabled through the update/disable hooks
	 * above, and the CRTC enable/disable independently controls
	 * whether anything scans out at all, but the firmware doesn't
	 * give us a CRTC-level control for that.
	 */
	vc4_cursor_plane_atomic_disable(crtc->cursor, crtc->cursor->state);
	vc4_plane_set_primary_blank(crtc->primary, true);
}