#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_mode_fb_cmd2 {int height; int* pitches; int /*<<< orphan*/  width; int /*<<< orphan*/  pixel_format; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct cirrus_device* dev_private; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct cirrus_fbdev {TYPE_1__ helper; } ;
struct cirrus_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cirrus_check_framebuffer (struct cirrus_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int cirrus_gem_create (struct drm_device*,int,int,struct drm_gem_object**) ; 
 int drm_format_plane_cpp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cirrusfb_create_object(struct cirrus_fbdev *afbdev,
			       const struct drm_mode_fb_cmd2 *mode_cmd,
			       struct drm_gem_object **gobj_p)
{
	struct drm_device *dev = afbdev->helper.dev;
	struct cirrus_device *cdev = dev->dev_private;
	u32 bpp;
	u32 size;
	struct drm_gem_object *gobj;
	int ret = 0;

	bpp = drm_format_plane_cpp(mode_cmd->pixel_format, 0) * 8;

	if (!cirrus_check_framebuffer(cdev, mode_cmd->width, mode_cmd->height,
				      bpp, mode_cmd->pitches[0]))
		return -EINVAL;

	size = mode_cmd->pitches[0] * mode_cmd->height;
	ret = cirrus_gem_create(dev, size, true, &gobj);
	if (ret)
		return ret;

	*gobj_p = gobj;
	return ret;
}