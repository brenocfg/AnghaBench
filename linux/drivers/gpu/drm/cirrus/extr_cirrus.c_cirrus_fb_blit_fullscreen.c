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
struct drm_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int cirrus_fb_blit_rect (struct drm_framebuffer*,struct drm_rect*) ; 

__attribute__((used)) static int cirrus_fb_blit_fullscreen(struct drm_framebuffer *fb)
{
	struct drm_rect fullscreen = {
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	};
	return cirrus_fb_blit_rect(fb, &fullscreen);
}