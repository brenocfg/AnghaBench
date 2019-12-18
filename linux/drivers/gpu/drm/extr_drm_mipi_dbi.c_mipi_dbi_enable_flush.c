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
struct mipi_dbi_dev {int enabled; int /*<<< orphan*/  backlight; int /*<<< orphan*/  drm; } ;
struct drm_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_enter (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 int /*<<< orphan*/  mipi_dbi_fb_dirty (struct drm_framebuffer*,struct drm_rect*) ; 

void mipi_dbi_enable_flush(struct mipi_dbi_dev *dbidev,
			   struct drm_crtc_state *crtc_state,
			   struct drm_plane_state *plane_state)
{
	struct drm_framebuffer *fb = plane_state->fb;
	struct drm_rect rect = {
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	};
	int idx;

	if (!drm_dev_enter(&dbidev->drm, &idx))
		return;

	dbidev->enabled = true;
	mipi_dbi_fb_dirty(fb, &rect);
	backlight_enable(dbidev->backlight);

	drm_dev_exit(idx);
}