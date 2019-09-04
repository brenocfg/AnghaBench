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
struct tinydrm_device {int /*<<< orphan*/  (* fb_dirty ) (struct drm_framebuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct mipi_dbi {int enabled; int /*<<< orphan*/  backlight; struct tinydrm_device tinydrm; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_framebuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mipi_dbi_enable_flush(struct mipi_dbi *mipi,
			   struct drm_crtc_state *crtc_state,
			   struct drm_plane_state *plane_state)
{
	struct tinydrm_device *tdev = &mipi->tinydrm;
	struct drm_framebuffer *fb = plane_state->fb;

	mipi->enabled = true;
	if (fb)
		tdev->fb_dirty(fb, NULL, 0, 0, NULL, 0);

	backlight_enable(mipi->backlight);
}