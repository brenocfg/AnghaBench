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
struct drm_mode_fb_cmd2 {scalar_t__ pixel_format; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_BGRX8888 ; 
 scalar_t__ DRM_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  EINVAL ; 
 struct drm_framebuffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct drm_framebuffer* drm_gem_fb_create (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2 const*) ; 

__attribute__((used)) static struct drm_framebuffer *
bochs_gem_fb_create(struct drm_device *dev, struct drm_file *file,
		    const struct drm_mode_fb_cmd2 *mode_cmd)
{
	if (mode_cmd->pixel_format != DRM_FORMAT_XRGB8888 &&
	    mode_cmd->pixel_format != DRM_FORMAT_BGRX8888)
		return ERR_PTR(-EINVAL);

	return drm_gem_fb_create(dev, file, mode_cmd);
}