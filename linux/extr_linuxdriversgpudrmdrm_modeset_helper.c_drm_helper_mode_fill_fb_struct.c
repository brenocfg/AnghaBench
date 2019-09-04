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
struct drm_mode_fb_cmd2 {int /*<<< orphan*/  flags; int /*<<< orphan*/ * modifier; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_framebuffer {int /*<<< orphan*/  flags; int /*<<< orphan*/  modifier; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_get_format_info (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 

void drm_helper_mode_fill_fb_struct(struct drm_device *dev,
				    struct drm_framebuffer *fb,
				    const struct drm_mode_fb_cmd2 *mode_cmd)
{
	int i;

	fb->dev = dev;
	fb->format = drm_get_format_info(dev, mode_cmd);
	fb->width = mode_cmd->width;
	fb->height = mode_cmd->height;
	for (i = 0; i < 4; i++) {
		fb->pitches[i] = mode_cmd->pitches[i];
		fb->offsets[i] = mode_cmd->offsets[i];
	}
	fb->modifier = mode_cmd->modifier[0];
	fb->flags = mode_cmd->flags;
}