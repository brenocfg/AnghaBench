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

/* Variables and functions */
 int radeon_cursor_move_locked (struct drm_crtc*,int,int) ; 
 int /*<<< orphan*/  radeon_lock_cursor (struct drm_crtc*,int) ; 

int radeon_crtc_cursor_move(struct drm_crtc *crtc,
			    int x, int y)
{
	int ret;

	radeon_lock_cursor(crtc, true);
	ret = radeon_cursor_move_locked(crtc, x, y);
	radeon_lock_cursor(crtc, false);

	return ret;
}