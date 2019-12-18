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
struct drm_plane_state {int crtc_x; int crtc_y; unsigned int crtc_w; unsigned int crtc_h; } ;

/* Variables and functions */

__attribute__((used)) static void set_crtc(struct drm_plane_state *plane_state,
		     int crtc_x, int crtc_y,
		     unsigned crtc_w, unsigned crtc_h)
{
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_w = crtc_w;
	plane_state->crtc_h = crtc_h;
}