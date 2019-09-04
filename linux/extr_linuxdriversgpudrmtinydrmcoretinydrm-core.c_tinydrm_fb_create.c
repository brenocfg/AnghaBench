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
struct tinydrm_device {int /*<<< orphan*/  fb_funcs; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct tinydrm_device* dev_private; } ;

/* Variables and functions */
 struct drm_framebuffer* drm_gem_fb_create_with_funcs (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_framebuffer *
tinydrm_fb_create(struct drm_device *drm, struct drm_file *file_priv,
		  const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct tinydrm_device *tdev = drm->dev_private;

	return drm_gem_fb_create_with_funcs(drm, file_priv, mode_cmd,
					    tdev->fb_funcs);
}