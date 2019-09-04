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
struct drm_framebuffer {int /*<<< orphan*/  dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rockchip_drm_psr_flush_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_drm_fb_dirty(struct drm_framebuffer *fb,
				 struct drm_file *file,
				 unsigned int flags, unsigned int color,
				 struct drm_clip_rect *clips,
				 unsigned int num_clips)
{
	rockchip_drm_psr_flush_all(fb->dev);
	return 0;
}