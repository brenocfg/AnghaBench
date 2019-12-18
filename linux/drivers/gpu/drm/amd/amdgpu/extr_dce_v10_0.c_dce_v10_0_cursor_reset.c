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
struct amdgpu_crtc {int /*<<< orphan*/  cursor_y; int /*<<< orphan*/  cursor_x; scalar_t__ cursor_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce_v10_0_cursor_move_locked (struct drm_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v10_0_lock_cursor (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  dce_v10_0_show_cursor (struct drm_crtc*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dce_v10_0_cursor_reset(struct drm_crtc *crtc)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	if (amdgpu_crtc->cursor_bo) {
		dce_v10_0_lock_cursor(crtc, true);

		dce_v10_0_cursor_move_locked(crtc, amdgpu_crtc->cursor_x,
					     amdgpu_crtc->cursor_y);

		dce_v10_0_show_cursor(crtc);

		dce_v10_0_lock_cursor(crtc, false);
	}
}