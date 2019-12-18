#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {TYPE_2__* primary; scalar_t__ state; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct TYPE_3__ {int /*<<< orphan*/  rotation; } ;

/* Variables and functions */
 int drm_framebuffer_check_src_coords (int,int,int,int,struct drm_framebuffer const*) ; 
 int /*<<< orphan*/  drm_mode_get_hv_timing (struct drm_display_mode const*,int*,int*) ; 
 scalar_t__ drm_rotation_90_or_270 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int,int) ; 

int drm_crtc_check_viewport(const struct drm_crtc *crtc,
			    int x, int y,
			    const struct drm_display_mode *mode,
			    const struct drm_framebuffer *fb)

{
	int hdisplay, vdisplay;

	drm_mode_get_hv_timing(mode, &hdisplay, &vdisplay);

	if (crtc->state &&
	    drm_rotation_90_or_270(crtc->primary->state->rotation))
		swap(hdisplay, vdisplay);

	return drm_framebuffer_check_src_coords(x << 16, y << 16,
						hdisplay << 16, vdisplay << 16,
						fb);
}