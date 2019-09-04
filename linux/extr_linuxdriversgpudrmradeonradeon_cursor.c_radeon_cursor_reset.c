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
struct radeon_crtc {int /*<<< orphan*/  cursor_y; int /*<<< orphan*/  cursor_x; scalar_t__ cursor_bo; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_cursor_move_locked (struct drm_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_lock_cursor (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  radeon_show_cursor (struct drm_crtc*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

void radeon_cursor_reset(struct drm_crtc *crtc)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	if (radeon_crtc->cursor_bo) {
		radeon_lock_cursor(crtc, true);

		radeon_cursor_move_locked(crtc, radeon_crtc->cursor_x,
					  radeon_crtc->cursor_y);

		radeon_show_cursor(crtc);

		radeon_lock_cursor(crtc, false);
	}
}